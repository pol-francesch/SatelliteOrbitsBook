##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Ex_2-4
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/polfr/Documents/Stuttgart/Stuttgart
ProjectPath            :=C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=polfr
Date                   :=15/06/2020
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
ObjectsFileList        :="Ex_2-4.txt"
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
Objects0=$(IntermediateDirectory)/SAT_Kepler.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_Time.cpp$(ObjectSuffix) $(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/SAT_Kepler.cpp$(ObjectSuffix): SAT_Kepler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_Kepler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_Kepler.cpp$(DependSuffix) -MM SAT_Kepler.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4/SAT_Kepler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_Kepler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_Kepler.cpp$(PreprocessSuffix): SAT_Kepler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_Kepler.cpp$(PreprocessSuffix) SAT_Kepler.cpp

$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix): SAT_VecMat.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_VecMat.cpp$(DependSuffix) -MM SAT_VecMat.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4/SAT_VecMat.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_VecMat.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_VecMat.cpp$(PreprocessSuffix): SAT_VecMat.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_VecMat.cpp$(PreprocessSuffix) SAT_VecMat.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/SAT_Time.cpp$(ObjectSuffix): SAT_Time.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_Time.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_Time.cpp$(DependSuffix) -MM SAT_Time.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4/SAT_Time.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_Time.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_Time.cpp$(PreprocessSuffix): SAT_Time.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_Time.cpp$(PreprocessSuffix) SAT_Time.cpp

$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix): SAT_RefSys.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SAT_RefSys.cpp$(DependSuffix) -MM SAT_RefSys.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/polfr/Documents/Stuttgart/Stuttgart/Ex_2-4/SAT_RefSys.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SAT_RefSys.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SAT_RefSys.cpp$(PreprocessSuffix): SAT_RefSys.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SAT_RefSys.cpp$(PreprocessSuffix) SAT_RefSys.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


