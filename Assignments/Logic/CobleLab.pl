%Number One
%Facts
food(burger).
food(sandwich).
food(pizza).
lunch(sandwich).
dinner(pizza).

%Rules
meal(X):-food(X).


%Two
%Facts
studies(charlie, csc135). 
studies(olivia, csc135). 
studies(jack, csc131).
studies(arthur, csc134). 
teaches(kirke, csc135). 
teaches(collins, csc131).
teaches(collins, csc171).
teaches(juniper, csc134).

%Rules
professor(X,Y):- teaches(X,C), studies(Y,C).


%Three
%Facts
owns(jack, car(bmw)).
owns(john, car(chevy)). 
owns(olivia, car(civic)). 
owns(jane, car(chevy)).

%Rules
sedan(X):- X = car(bmw); X = car(civic).
truck(X):- X = car(chevy).

%Four
%Facts
cat(fubby). 
blackspot(fubby). 
dog(figaro).
whitespot(figaro).

%Rules
ownsPet(mary,X):- cat(X), blackspot(X).
loves(X, Y):- ownsPet(X, Y).