a="25 37 23 26 30 40 25 26 39 32 21 26 19 27 32 23 18 26 34 18 31 35 21 33 33 9 16 32 35 42 15 24"
lst=a.split()
lst=[int(i) for i in lst]
lst.sort()

print(len(lst))
print(lst)

print("\nQ1:",lst[7])
print("Q2:",lst[15])
print("Q3:",lst[23])

print("IRQ:", lst[23]-lst[7])

print("\nMin:",lst[0])
print("Max:",lst[31])


print("\nOutliers:")
flag=1
for i in lst:
    if i<lst[7]-1.5*(lst[23]-lst[7]) or i>lst[23]+1.5*(lst[23]-lst[7]):
        print(i)
        flag=0
if flag:
    print("No Outliers Found!")

# Class of with 20
#  0-20, 20-40, 40-60
# Make the Frequency Table

print("\nFrequency Table:")
ranges=[(0,20),(20,40),(40,60)]
x=[]
f=[]
cf=[]
fx=0

for s,e in ranges:
    x.append((e+s)/2)
    f.append(len([i for i in lst if s<=i<e]))
    cf.append(sum(f))
    fx+=x[-1]*f[-1]

print("x:",x)
print("f:",f)
print("cf:",cf)

# mean = sum of fx/sum of f
mean=fx/sum(f)
print("\nMean:",mean)

# median = L + ((n/2 - cf)/f) * w
L=20
n=32
w=20
fl=6
f=24

median=L+((n/2-fl)/f)*w
print("Median:",median)

mode=mean - 3*(mean-median)
print("Mode:",mode)
