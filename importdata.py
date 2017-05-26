import pandas as pd
import pylab as pl
import numpy as np
import string
import re

##Returns all names to lowercase letters
def lowercase(name):
    return name.lower()
    
##Gets rid of any extra or excess white space at ends and middle
def no_spaces(name):
    name = name.lstrip()
    name = name.strip()
    name = " ".join(name.split())
    return name
    
##Gets rid of legal control terms and punctuation
def no_legal(name):
    name = name.translate(None, string.punctuation)
    legal_terms = ["inc", "corporation", "llc", "corp", "co", "incorporated", "company", "group", "and", "its", "subsidiaries", "plc", "llp", "all"]
    for item in legal_terms:
       end = len(name)
       filter = len(item)
       if name.endswith(' ' +item):
           name = name[:end-filter]
       if name.startswith(item + ' '):
           name = name[len(item)+1:end-1]
       term = ' ' + item + ' '
       middle = name.find(term)
       if middle != -1:
           name = name[0:middle] + " " + name[middle+filter+1:end-1]
    name = no_spaces(name)
    return name
    
##Expands company abbreviations into full company names
#def expand(name):

##Splits string into bigrams (sets of 2 letters)
def bigrams(name):
    out = set()
    for i in range(len(name)):
        out.add(name[i:i+2])
    return out
    
##Calculates the Jaccard Index for bigrams of a pair of names
def jaccard(name1, name2):
    #Base Case: same string
    if(name1 == name2):
        return 1
    #Ensure name2 is always shorter than name1
    if(len(name1) < len(name2)):
        tmp = name2
        name2 = name1
        name1 = tmp
    bigram1 = bigrams(name1)
    bigram2 = bigrams(name2)
    n = len(bigram1.intersection(bigram2))
    cardinality_check = len(bigram2)/float(len(bigram1))
    if(cardinality_check >= 0.5):
        return n/(float(len(bigram1) + len(bigram2) -n))
    else:
        words = name1.split()
        if name2 in name1:
            return 1
        for item in words:
            if(item == name2):
                return 1
        return -1
#Read in file as dataframe
df = pd.read_csv("CyberLiabilityRead.csv")
#Convert Insured Name column type to string
df['Insured Name'].astype(basestring)
dict_names = df.loc[0:252, 'Insured Name']
#Convert dict_names to a list called names
names = dict_names.tolist()
names_total = names
names = [lowercase(corp) for corp in names]
names = [no_spaces(corp) for corp in names] 
names = [no_legal(corp) for corp in names]
i = 0
index = [];
indexm = [];
name1 = raw_input('Enter Insured Name--> ')
name1 = lowercase(name1)
name1 = no_spaces(name1)
name1 = no_legal(name1)
for name2 in names:
    j = 0
    value = jaccard(name1, name2)
    if(value > 0.4):
        if(value < 0.7):
            indexm.append(i)
        else:    
            index.append(i)
        j += 1
    i += 1
for z in indexm:
    name3 = names[z]
    name4 = name1
    len4 = len(name4)
    len3 = len(name3)
    #Always make len3 the smallest length
    if(len4 < len3):
        tmp = name4
        name4 = name3
        name3 = tmp
    len4 = len(name4)
    len3 = len(name3)
    value1 = jaccard(name3[0:len3/2], name4[0:len3/2])
    value2 = jaccard(name3[len3/2:len3-1], name4[len3/2:len3-1])
    if((value1 > 0.7) and (value2 > 0.7)):
        index.append(z)
for i1 in index:
    print names_total[i1]