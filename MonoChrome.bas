public dim shared as integer i,dpsec = 30,Ofile = 0

function fdd(byval s as string) as integer
    dim as integer i
    for i=0 to len(s)-1
        if chr(s[i]) = "$" then
            return i+1
        end if
    next
    
    return -1
end function

sub dp(byval s as string)
    dim as integer xal = 0
    for i = 0 to len(s)-1
        if chr(s[i]) = "%" then
            xal = i+1
            while chr(s[xal]) <> "#" 
                xal+=1 
            wend
            shell(mid(s,i+2,xal-i-1))
            color 12
            print "Warning:[SYSTEM]Executing:\";
            color 10
        else
            if chr(s[i]) <> "#" then
                print chr(s[i]);
                sleep dpsec
            else
                print
            end if
        end if
    next
end sub
sub BIOS()
    print "Not Supported Yet."
end sub

sub init()
    cls
    color 10
    print "Fed-OS Version 1.1[Using GNU License GPL V2.0]"
    print "Now Time is ";date;" ";time
    print "Press F2 To enter BIOS"
    sleep 500
    print "Self-Posting..."
    sleep 1000
    print "Memory:536870912KB OK."
    sleep 500
    dp("System Inited.Loading Chatting Interface..."):sleep 500:dp("Done#")
    
end sub

function ffold(byval s as string) as integer
    dim i as integer
    for i=0 to len(s)-1
        if chr(s[i]) = "\" then return i+1
    next
end function
sub PlayScript(byval dc as integer)
    dim as string s,user(1001),text(1001)
    dim as integer ls = Ofile+2,total = 0,p,nex(1001),nt,i
    open "Scripts\scr"+str(dc)+".log" for input as #(Ofile+1):Ofile+=1
    for i = 1 to 1001
        nex(i) = 0
    next
    
    line input #1,s
    if (s <> "@Characters_Start") then 
        print "Script Error!"
        exit sub
    end if
    do
        line input #1,s
        if s = "@Characters_End" then exit do
        total += 1:user(total) = left(s,ffold(s)-1)
        Ofile+=1:open "Characters\" + s for input as #Ofile
    loop
    
    s = "":p = 0:nt = total
    for i = 1 to nt
        line input #(ls+i-1),text(i)
    next
    
    do while (total > 0)
        p +=1:if p>nt then p = 1
        if nex(p) <> -1 then
            s = text(p)
            s = mid(s,nex(p)+1)
            text(p) = s
            nex(p) = fdd(s)
            dp("[" + user(p) + "]:" + mid(s,1,fdd(s)-1))
            print
            if nex(p) = -1 then total-=1
            if total>0 then sleep
        end if
    loop
    
    color 12
    print "[Done.]"
    color 10
    close
end sub

init
'Main
dim as integer dc = 0
open "Save.cfg" for input as #1:Ofile+=1
input #1,dc
close #1:Ofile -=1
PlayScript(dc)
sleep:end
