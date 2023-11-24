```
type1:
    print case
    for i enumerate all test date
    begin 
        if level is the same   
            record this data in a new array "out"
    end
    sort the "out" array by score(decresing)>>ID(dictionary increasing order)
    if element not null
        print all the element in "out"
    else 
        print NA

type2:
    print case
    for i enumerate all test date
    begin 
        if sitenumber is the same   
            sum up score in "sum"
            record present number of answers in "cnt"
    end 
    if no answer 
        print NA
    else 
        print number of answer
        print sum

type3:
//桶排
set a array "ans" to record the exist time of the corresponding sitenumber    
    print case  
    for i enumerate all test date
    begin 
        if date is the same   
            ans[sitenumber of this data]++
            record maximum exist time
    end
    //print part
    for i enumerate exist times from maximum to 1
    begin
        for j enumerate sitenumber in a increasing order
        begin
            if ans[j] == i
                print j 
                print ans[j]
                set flag_haveans to 1
        end
    end
    if noans
        print NA
```

