all: compile

build:
	java -classpath antlrworks-1.4.3.jar org.antlr.Tool Lab6.g

compile: build
	javac -classpath antlrworks-1.4.3.jar *.java

run:
	java -classpath .:antlrworks-1.4.3.jar Lab6Parser

edit:
	java -jar antlrworks-1.4.3.jar

clean:
	$(RM) -r *.java *.class *.tokens output
