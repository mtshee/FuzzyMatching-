def jaccard(name1, name2):
    name1 = str(name1)
    name2 = str(name2)
    str1 = set(name1.split())
    str2 = set(name2.split())
    return float(len(str1 & str2)) / len(str1 | str2)
    
name1 = 'ibm'
name2 = 'international business machines'
name3 = 'at&t'
name4 = 'att'
name5 = 'ti'
name12 = 'ni'
name6 = 'texas instruments'
name7 = 'national instruments'
name8 = 'apple"'
name9 = 'aple'
name10 = 'microsofit'
name11 = 'microsoft'
name13 = 'fitbit'
name14 = 'google'
print jaccard(name1, name2)
print jaccard(name3, name4)
print jaccard(name5, name12)
print jaccard(name5, name6)
print jaccard(name12, name7)
print jaccard(name8, name9)
print jaccard(name10, name11)
print jaccard(name13, name14)
