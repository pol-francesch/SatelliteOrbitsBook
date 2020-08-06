##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Ex_3-1
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/polfr/Documents/Stuttgart/Stuttgart
ProjectPath            :=C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_3-1
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=polfr
Date                   :=17/06/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Ex_3-1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS := -std=c++14 -Wall -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_Force.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_3-1/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/SAT_Force.cpp$(ObjectSuffix): SAT_Force.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_Force.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_Force.cpp$(DependSuffix) -MM SAT_Force.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_3-1/SAT_Force.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_Force.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_Force.cpp$(PreprocessSuffix): SAT_Force.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_Force.cpp$(PreprocessSuffix) SAT_Force.cpp

$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix): SAT_VecMat.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_VecMat.cpp$(DependSuffix) -MM SAT_VecMat.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_3-1/SAT_VecMat.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_VecMat.cpp$(PreprocessSuffix): SAT_VecMat.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_VecMat.cpp$(PreprocessSuffix) SAT_VecMat.cpp

$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix): SAT_RefSys.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_RefSys.cpp$(DependSuffix) -MM SAT_RefSys.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_3-1/SAT_RefSys.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_RefSys.cpp$(PreprocessSuffix): SAT_RefSys.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_RefSys.cpp$(PreprocessSuffix) SAT_RefSys.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


