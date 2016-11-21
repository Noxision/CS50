from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    rows = db.execute("SELECT * FROM portfolio WHERE session_id = :id ORDER BY symbol", id=session["user_id"])
    
    total = 0
    
    for i in rows:
        stock = lookup(i["symbol"])
        i["price"] = stock["price"]
        i["total"] = i["price"] * i["shares"]
        total += i["total"]
        i["price"] = usd(i["price"])
        i["total"] = usd(i["total"])
        
        
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    cash = cash[0]['cash']
    total = total + cash
    cash = usd(cash)
    total = usd(total)

    return render_template("index.html", rows=rows, cash=cash, total=total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol")
        elif not request.form.get("shares"):
            return apology("missing shares")
        elif not request.form.get("shares").isdigit():
            return apology("invalid shares")
        elif type(request.form.get("shares")) == float:
            return apology("invalid shares")
        elif int(request.form.get("shares")) < 1:
            return apology("invalid shares")
            
        stock = lookup(request.form.get("symbol"))
            
        if stock == None:
            return apology("invalid symbol")
            
        name = stock["name"]
        symbol = stock["symbol"].upper()
        price = stock["price"]
        shares = int(request.form.get("shares"))
        
        cost = shares * price
        
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        cash = cash[0]['cash']
        
        if cost > cash:
            return apology("can't afford")
            
        rows = db.execute("SELECT * FROM portfolio WHERE session_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        
        if not rows:
            db.execute("INSERT INTO portfolio (session_id, symbol, shares, name) VALUES (:id, :symbol, :shares, :name)", id=session["user_id"], symbol=symbol, shares=shares, name=name)
        else:
            db.execute("UPDATE portfolio SET shares = shares + :shares WHERE session_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol, shares=shares)
        
        cash = cash - cost
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash, id=session["user_id"])
        
        db.execute("INSERT INTO history (session_id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id=session["user_id"], symbol=symbol, shares=shares, price=price)

        flash('Bought!')
        # redirect user to home page
        return redirect(url_for("index"))
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    rows = db.execute("SELECT * FROM history WHERE session_id = :id", id=session["user_id"])
    
    for i in rows:
        i["price"] = usd(i["price"])

    return render_template("history.html", rows=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("username"):
            return apology("missing username")
        elif not request.form.get("password"):
            return apology("missing password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol")
            
        stock = lookup(request.form.get("symbol"))
            
        if stock == None:
            return apology("invalid symbol")

        # render quoted page
        return render_template("quoted.html", name = stock["name"], symbol = stock["symbol"], price = stock["price"])

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()

    # username chaeck
    def checkName(name):
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=name)
        if len(rows) != 0:
            return 0
        return 1
            
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("missing username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("missing password")
        
        # ensure passwords match    
        elif request.form.get("password") != request.form.get("passwordConfirm"):
            return apology("passwords don't match")
            
        elif checkName(request.form.get("username")) != 1:
            return apology("username taken")
        
        # query database for username
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash = pwd_context.encrypt(request.form.get("password")))
        
        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash('Registered!')
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol")
        elif not request.form.get("shares"):
            return apology("missing shares")
        elif not request.form.get("shares").isdigit():
            return apology("invalid shares")
        elif type(request.form.get("shares")) == float:
            return apology("invalid shares")
        elif int(request.form.get("shares")) < 1:
            return apology("invalid shares")
            
        stock = lookup(request.form.get("symbol"))
            
        if stock == None:
            return apology("invalid symbol")

        name = stock["name"]
        symbol = stock["symbol"].upper()
        price = stock["price"]
            
        rows = db.execute("SELECT * FROM portfolio WHERE session_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        
        if not rows:
            return apology("symbol not owned")
            
        shares = int(request.form.get("shares"))
        
        if rows[0]["shares"] < shares:
            return apology("too many shares")
        
        if rows[0]["shares"] == shares:
            db.execute("DELETE FROM portfolio WHERE session_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        else:
            db.execute("UPDATE portfolio SET shares = shares - :shares WHERE session_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol, shares=shares)
    
        cost = shares * price
        
        db.execute("UPDATE users SET cash = cash + :cost WHERE id = :id", id=session["user_id"], cost=cost)
        
        db.execute("INSERT INTO history (session_id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id=session["user_id"], symbol=symbol, shares=-shares, price=price)

        flash('Sold!')
        # redirect user to home page
        return redirect(url_for("index"))
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")
        
@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add cash."""
    
# if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure cash was submitted
        if not request.form.get("cash"):
            return apology("missing cash")
        
        try:
            float(request.form.get("cash"))
        except:
            return apology("invalid cash")
        
        if float(request.form.get("cash")) <= 0:
            return apology("invalid cash")

        # query database for username
        db.execute("UPDATE users SET cash = cash + :cost WHERE id = :id", id=session["user_id"], cost=request.form.get("cash"))

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("cash.html")