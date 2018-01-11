# -*- coding: utf-8 -*-
"""
Created on Sat Nov 07 20:13:35 2015

@author: dan
"""

class state:
    
    myindextable=[]
    queue=[]
    myqueue=[]
    mynewstate=[]

    mySy=[]
    output=[]
    def __init__ (self,str,l):
            self.mstate=str
            self.oldstate=str
            self.myindextable=l
            self.mm=0
            self.closure()
            self.d={}
            for item in self.myindextable[0][1:-1]:
                self.d[item]=""
                
    def closure(self):
    
        t1=self.mstate.split(',')


        for item in t1:
            #double check
            if self.myindextable[int(item)][-1]!="":
                if t1.count(self.myindextable[int(item)][-1])==0:
                    self.mstate=self.mstate+","+self.myindextable[int(item)][-1]
        
        t3=self.mstate
        t1=t3.split(',')
        t4=self.oldstate
        for item in t1:
            #double check
            if self.myindextable[int(item)][-1]!="":
                if t1.count(self.myindextable[int(item)][-1])==0:
                    t4=t4+","+self.myindextable[int(item)][-1]       
        
        while t4!=self.mstate:
            self.mstate=t4
            t1=t4.split(',')
            t4=self.oldstate
            for item in t1:
                 #double check
                 if self.myindextable[int(item)][-1]!="":
                      if t1.count(self.myindextable[int(item)][-1])==0:                     
                          t4=t4+","+self.myindextable[int(item)][-1]   
                     
                            
                
        self.mySy.append(self.oldstate)  
        if self.output.count(self.mstate)==0:
            self.output.append(self.mstate)
        self.mm=len(self.output)
        
        print "E-closure("+str(self.oldstate)+")"+" = {"+str(self.mstate)+"}="+str(self.mm)
       
                        
        
        
        #self.move()
            
    #--------------------        
    def move(self):
        print "\n"
        print 'Mark   '+str(self.mm)
        
        t2=self.mstate.split(',')
        for i in range(1,len(self.myindextable[0])-1):
            t3=''            
            for item in t2:
                if t3=="":
                    if self.myindextable[int(item)][i]!="":
                        t3=t3+self.myindextable[int(item)][i]
                else:
                    if self.myindextable[int(item)][i]!="":
                        t3=t3+","+self.myindextable[int(item)][i]
            if t3!="":
                print "{"+str(self.mstate)+"}--"+self.myindextable[0][i]+"-->"+"{"+t3+"}"
                
                #print self.d
                if self.mySy.count(t3)==0:  
                    
                    temp=state(t3,self.myindextable)
                    self.queue.append(temp)
                    self.myqueue.append(temp)
                else:
                    temp=state(t3,self.myindextable)
                self.d[self.myindextable[0][i]]=temp.mm             
                                                
    
    
    
    


#-----------------------------
def Readfile():
    mylist=[]
    f=open("input.txt",'r')
    for line in f:
            mylist.append(line)
    return mylist        



def main():
    print "start"
    #notation table
    IS=""    
    FS=""
    TS=""
    indextable=[]
    
    
    #read input
    rawfile=Readfile()
    #print(rawfile)
    for i in range(len(rawfile)):
        tem=rawfile[i]
        if i==0:
            s1=tem.find('{')
            s2=tem.find('}')
            s=tem[s1+1:s2]
            IS=s
        elif i==1:
            s1=tem.find('{')
            s2=tem.find('}')
            s=tem[s1+1:s2]
            FS=s
        elif i==2:
            s1=tem.find(':')
            TS=tem[s1+1:]
        elif i==3:
            line=tem.split('\n')
            line=line[0].split('\t')
            indextable.append(line)
        else:
            line=tem.split('\n')
            line=line[0].split('\t{')
            for i in range(1,len(line)):
                t=line[i].find('}')
                    line[i]=line[i][:t]
            indextable.append(line)
    #print indextable
        
    
    mystate=state(IS,indextable)
 
  # mystate.closure()
    mystate.move()
    while len(mystate.queue)!=0 :
        mystate.queue.pop(0).move()
    
    mystate.myqueue.insert(0,mystate)

    myFS=""  
    KFS=FS.split(",")
    for item in mystate.myqueue:
        t5=item.mstate.split(",")
        for i in t5:
            if KFS.count(i)!=0:
                if myFS=="":
                    myFS=myFS+str(item.mm)
                    
                else:
                    myFS=myFS+","+str(item.mm)
    
    print "\n"
    print 'Initial State: {1}'
    print 'Final States: {'+myFS+'}'
    tem=''
    for i in indextable[0][:-1]:
        if tem=="":
            tem=i
        else:
            tem=tem+'\t'+i
    print tem
    for item in mystate.myqueue:
        temp=str(item.mm)
        for i in indextable[0][1:-1]:
            temp=temp+"\t"+"{"+str(item.d[i])+"}"
        print temp
        
        
    
        
    
        
#-----------------------------


main()
print "end"
