
def make_table(rows,labels=None,centered=False):
    mainString=""
    maxlist=[]
    for i in range(0,len(rows[0])):
        if labels!=None:
            m=len(str(labels[i]))
        else:
            m=0
        for a in rows:
            if len(str(a[i]))>m:
                m=len(str(a[i]))
        maxlist.append(m+1)

    f="┌"
    for i in range(len(maxlist)):
        if i is not len(maxlist)-1:
            f=f+("─"*(maxlist[i]+1))+"┬"
        else:
            f=f+("─"*(maxlist[i]+1))+"┐"
    mainString=mainString+f+"\n"

    f="├"
    n=0
    if labels!=None:
        if centered==False:
            main="│ "
            for i in range(0,len(labels)):
                b=" "*(maxlist[i]-len(str(labels[i]))-i+n)
                if i is not len(labels)-1:
                    main=main+str(labels[i])+str(b)+"│ "
                else:
                    main=main+str(labels[i])+str(b)+"│"
                if i<len(maxlist)-1:
                    f=f+(("─")*(maxlist[i]+1))+"┼"
                else:
                    f=f+(("─")*(maxlist[i]+1))+"┤"
                n=n+1
            mainString=mainString+main+"\n"
            mainString=mainString+f+"\n"
        else:
            main="│ "
            for i in range(0,len(labels)):
                bs=maxlist[i]-len(str(labels[i]))+1
                if bs%2==0:
                    b1=bs/2-1
                    b2=bs/2
                    b11=" "*int(b1)
                    b22=" "*int(b2)
                    if i is not len(labels)-1:
                        main=main+str(b11)+str(labels[i])+str(b22)+"│ "
                    else:
                        main=main+str(b11)+str(labels[i])+str(b22)+"│"
                    if i<len(maxlist)-1:
                        f=f+(("─")*(maxlist[i]+1))+"┼"
                    else:
                        f=f+(("─")*(maxlist[i]+1))+"┤"
                    n=n+1
                else:
                    b1=(bs/2)-0.5-1
                    b2=(bs/2)-0.5+1
                    b11=" "*int(b1)
                    b22=" "*int(b2)
                    if i is not len(labels)-1:
                        main=main+str(b11)+str(labels[i])+str(b22)+"│ "
                    else:
                        main=main+str(b11)+str(labels[i])+str(b22)+"│"
                    if i<len(maxlist)-1:
                        f=f+(("─")*(maxlist[i]+1))+"┼"
                    else:
                        f=f+(("─")*(maxlist[i]+1))+"┤"
                    n=n+1
                
            mainString=mainString+main+"\n"
            mainString=mainString+f+"\n"

    for i in range(0,len(rows)):
        if centered==False:
            main="│ "
            for j in range(0,len(rows[i])):
                b=" "*(maxlist[j]-len(str(rows[i][j])))
                if j is not len(rows[i])-1:
                    main=main+str(rows[i][j])+str(b)+"│ "
                else:
                    main=main+str(rows[i][j])+str(b)+"│"
            mainString=mainString+main+"\n"
        else:
            main="│ "
            for j in range(0,len(rows[i])):
                bs=maxlist[j]-len(str(rows[i][j]))+1
                if bs%2==0:
                    b1=bs/2-1
                    b2=bs/2
                    b11=" "*int(b1)
                    b22=" "*int(b2)
                    if j is not len(rows[i])-1:
                        main=main+str(b11)+str(rows[i][j])+str(b22)+"│ "
                    else:
                        main=main+str(b11)+str(rows[i][j])+str(b22)+"│"
                else:
                    b1=(bs/2)-0.5+1
                    b2=(bs/2)-0.5-1
                    b11=" "*int(b1)
                    b22=" "*int(b2)
                    if j is not len(rows[i])-1:
                        main=main+str(b22)+str(rows[i][j])+str(b11)+"│ "
                    else:
                        main=main+str(b22)+str(rows[i][j])+str(b11)+"│"

            mainString=mainString+main+"\n"
            
    f="└"
    for i in range(len(maxlist)):
        if i is not len(maxlist)-1:
            f=f+("─"*(maxlist[i]+1))+"┴"
        else:
            f=f+("─"*(maxlist[i]+1))+"┘"
    mainString=mainString+f+"\n"

    return mainString

# t=make_table(
#                 rows=[
#                     ["Pneumonoultramicroscopicsilicovolcanoconiosis",'a'],
#                     ["Hippopotomonstrosesquippedaliophobia",'a'],
#                     ["Supercalifragilisticexpialidocious",'a'],
#                     ["Pseudopseudohypoparathyroidism",'a'],
#                     ["Floccinaucinihilipilification",'a'],
#                     ["Antidisestablishmentarianism",'a'],
#                     [".",'a']
#                 ],
#                 labels=["My Favourite Long Words",'a'],
#                 centered=True
#             )

# print(t)