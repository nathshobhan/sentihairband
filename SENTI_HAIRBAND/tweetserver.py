import socket 
import tweepy
import requests
import json
import time

from multiprocessing import Process, Queue


que = Queue()

def toRemote():

        host = '' 
        port = 50000
        backlog = 0 
        size = 1024 
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        s.bind((host,port)) 
        s.listen(backlog) 
        client, address = s.accept()

        try:    
                temp = que.get()
        except:
                pass
        
        print "CONNECTED!!!"

        try:
                if temp == 0:
                        client.send("RRR\r")
                        print "0"
                if temp == 2:
                        client.send("BBB\r")
                        print "2"
                if temp == 4:
                        client.send("GGG\r")
                        print "4"
        except:

                pass

        time.sleep(2)
        client.close()



def fromTwitter():
        api = twitter.Api(consumer_key='<>',
                      consumer_secret='<>',
                      access_token_key='<>',
                      access_token_secret='<>')
        tweets = api.GetUserTimeline(screen_name="shobhan_nath")
        for tweet in tweets:

                data = json.dumps({"data":[{"text":tweet.text}]})

                r = requests.post("http://www.sentiment140.com/api/bulkClassifyJson",data=str(data))
        #               print str(data)
                r = r.json()["data"][0]
        #               print r
                print type(r['polarity'])
                que.put(r['polarity'])
                break
while (1):
        fromTwitter()
        toRemote()
        time.sleep(3)
