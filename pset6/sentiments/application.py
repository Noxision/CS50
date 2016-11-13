from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    positive, negative, neutral = 0.0, 0.0, 0.0
    
    i = 0

    for tweet in tweets:
        
        # instantiate analyzer
        analyzer = Analyzer()
        
        # analyze word
        score = analyzer.analyze(tweet.lower())
        
        if score > 0.0:
            positive += 1
        elif score < 0.0:
            negative += 1
        else:
            neutral += 1
        
        i += 1
        
    tweetsCount = 100.0
    if i < tweetsCount:
        tweetsCount = i
    
    positive = round(positive/tweetsCount, 1)
    negative = round(negative/tweetsCount, 1)
    neutral = round(neutral/tweetsCount, 1)
    
    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
