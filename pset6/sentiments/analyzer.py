import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives="positive-words.txt", negatives="negative-words.txt"):
        """Initialize Analyzer."""

        self.pw = list()
        self.nw = list()
        
        posit = open(positives, 'r')
        negat = open(negatives, 'r')
        
        for line in posit:
            if not line.startswith(";"):
                self.pw.append(line.rstrip("\n"))
                
        for line in negat:
            if not line.startswith(";"):
                self.nw.append(line.rstrip("\n"))
                
        posit.close()
        negat.close()
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        score = 0
        
        for tword in tokens:
            for pword in self.pw:
                if tword == pword:
                    score += 1
            for nword in self.nw:
                if tword == nword:
                    score -= 1
                    
        return score
