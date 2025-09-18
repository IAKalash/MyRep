dict = {"big" : "large", "commencement" : "start", "scheduled" : "planned", "for" : "on"}
str = "The big commencement of the project is for scheduled tomorrow"

sent = str.split(' ')
nstr = ""

for i in sent:
    if i.lower() in dict.keys():
        nstr += dict[i.lower()] + " "
    else:
        nstr += i + " "

print(nstr)
