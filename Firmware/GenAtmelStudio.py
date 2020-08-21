#!/bin/python
# This python script generates an AtmelStudio C Project File (*.cproj) and
#   an AtmelStudio Soultion File (*.atsln)
# Generated Files are placed in ./AtmelStudio/

import os
import shutil

print("-- Generating FW.atsln and FW.cproj -- ")

# Empty the ./AtmelStudio Directory (Delete all files in it)
shutil.rmtree("./AtmelStudio", ignore_errors=True)
os.mkdir("./AtmelStudio")

# Generate the Atmel Studio Solution File First:
AtmelSolText = """Microsoft Visual Studio Solution File, Format Version 12.00
# Atmel Studio Solution File, Format Version 11.00
VisualStudioVersion = 14.0.23107.0
MinimumVisualStudioVersion = 10.0.40219.1
Project("{54F91283-7BC4-4236-8FF9-10F437C3AD48}") = "FW", "FW.cproj", "{DCE6C7E3-EE26-4D79-826B-08594B9AD897}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|AVR = Debug|AVR
		Release|AVR = Release|AVR
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{DCE6C7E3-EE26-4D79-826B-08594B9AD897}.Debug|AVR.ActiveCfg = Debug|AVR
		{DCE6C7E3-EE26-4D79-826B-08594B9AD897}.Debug|AVR.Build.0 = Debug|AVR
		{DCE6C7E3-EE26-4D79-826B-08594B9AD897}.Release|AVR.ActiveCfg = Release|AVR
		{DCE6C7E3-EE26-4D79-826B-08594B9AD897}.Release|AVR.Build.0 = Release|AVR
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
EndGlobal
"""

solFile = open("AtmelStudio/FW.atsln", "w")
solFile.write(AtmelSolText)
solFile.close()

# Project Text
cprojFile = open("AtmelStudio/FW.cproj", "w")
sourceFiles = []
headerFiles = []

cprojPreamble = """<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003" ToolsVersion="14.0">
  <PropertyGroup>
    <SchemaVersion>2.0</SchemaVersion>
    <ProjectVersion>7.0</ProjectVersion>
    <ToolchainName>com.Atmel.AVRGCC8.C</ToolchainName>
    <ProjectGuid>dce6c7e3-ee26-4d79-826b-08594b9ad897</ProjectGuid>
    <avrdevice>ATmega328P</avrdevice>
    <avrdeviceseries>none</avrdeviceseries>
    <OutputType>Executable</OutputType>
    <Language>C</Language>
    <OutputFileName>$(MSBuildProjectName)</OutputFileName>
    <OutputFileExtension>.ELF</OutputFileExtension>
    <OutputDirectory>$(MSBuildProjectDirectory)/$(Configuration)</OutputDirectory>
    <AssemblyName>Firmware</AssemblyName>
    <Name>Firmware</Name>
    <RootNamespace>Firmware</RootNamespace>
    <ToolchainFlavour>Native</ToolchainFlavour>
    <KeepTimersRunning>true</KeepTimersRunning>
    <OverrideVtor>false</OverrideVtor>
    <CacheFlash>true</CacheFlash>
    <ProgFlashFromRam>true</ProgFlashFromRam>
    <RamSnippetAddress>0x20000000</RamSnippetAddress>
    <UncachedRange />
    <preserveEEPROM>true</preserveEEPROM>
    <OverrideVtorValue>exception_table</OverrideVtorValue>
    <BootSegment>2</BootSegment>
    <ResetRule>0</ResetRule>
    <eraseonlaunchrule>0</eraseonlaunchrule>
    <EraseKey />
    <avrtool>com.atmel.avrdbg.tool.simulator</avrtool>
    <avrtoolserialnumber />
    <avrdeviceexpectedsignature>0x1E950F</avrdeviceexpectedsignature>
    <com_atmel_avrdbg_tool_simulator>
      <ToolOptions xmlns="">
	<InterfaceProperties>
	</InterfaceProperties>
      </ToolOptions>
      <ToolType xmlns="">com.atmel.avrdbg.tool.simulator</ToolType>
      <ToolNumber xmlns="">
      </ToolNumber>
      <ToolName xmlns="">Simulator</ToolName>
    </com_atmel_avrdbg_tool_simulator>
  </PropertyGroup>
  <PropertyGroup Condition=" '$(Configuration)' == 'Release' ">
    <ToolchainSettings>
      <AvrGcc>
  <avrgcc.common.Device>-mmcu=atmega328p -B "%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/gcc/dev/atmega328p"</avrgcc.common.Device>
  <avrgcc.common.outputfiles.hex>True</avrgcc.common.outputfiles.hex>
  <avrgcc.common.outputfiles.lss>True</avrgcc.common.outputfiles.lss>
  <avrgcc.common.outputfiles.eep>True</avrgcc.common.outputfiles.eep>
  <avrgcc.common.outputfiles.srec>True</avrgcc.common.outputfiles.srec>
  <avrgcc.common.outputfiles.usersignatures>False</avrgcc.common.outputfiles.usersignatures>
  <avrgcc.compiler.general.ChangeDefaultCharTypeUnsigned>True</avrgcc.compiler.general.ChangeDefaultCharTypeUnsigned>
  <avrgcc.compiler.general.ChangeDefaultBitFieldUnsigned>True</avrgcc.compiler.general.ChangeDefaultBitFieldUnsigned>
  <avrgcc.compiler.symbols.DefSymbols>
    <ListValues>
      <Value>NDEBUG</Value>
    </ListValues>
  </avrgcc.compiler.symbols.DefSymbols>
  <avrgcc.compiler.directories.IncludePaths>
    <ListValues>
      <Value>%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/include</Value>
    </ListValues>
  </avrgcc.compiler.directories.IncludePaths>
  <avrgcc.compiler.optimization.level>Optimize for size (-Os)</avrgcc.compiler.optimization.level>
  <avrgcc.compiler.optimization.PackStructureMembers>True</avrgcc.compiler.optimization.PackStructureMembers>
  <avrgcc.compiler.optimization.AllocateBytesNeededForEnum>True</avrgcc.compiler.optimization.AllocateBytesNeededForEnum>
  <avrgcc.compiler.warnings.AllWarnings>True</avrgcc.compiler.warnings.AllWarnings>
  <avrgcc.linker.libraries.Libraries>
    <ListValues>
      <Value>libm</Value>
    </ListValues>
  </avrgcc.linker.libraries.Libraries>
  <avrgcc.assembler.general.IncludePaths>
    <ListValues>
      <Value>%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/include</Value>
    </ListValues>
  </avrgcc.assembler.general.IncludePaths>
</AvrGcc>
    </ToolchainSettings>
  </PropertyGroup>
  <PropertyGroup Condition=" '$(Configuration)' == 'Debug' ">
    <ToolchainSettings>
      <AvrGcc>
  <avrgcc.common.Device>-mmcu=atmega328p -B "%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/gcc/dev/atmega328p"</avrgcc.common.Device>
  <avrgcc.common.outputfiles.hex>True</avrgcc.common.outputfiles.hex>
  <avrgcc.common.outputfiles.lss>True</avrgcc.common.outputfiles.lss>
  <avrgcc.common.outputfiles.eep>True</avrgcc.common.outputfiles.eep>
  <avrgcc.common.outputfiles.srec>True</avrgcc.common.outputfiles.srec>
  <avrgcc.common.outputfiles.usersignatures>False</avrgcc.common.outputfiles.usersignatures>
  <avrgcc.compiler.general.ChangeDefaultCharTypeUnsigned>True</avrgcc.compiler.general.ChangeDefaultCharTypeUnsigned>
  <avrgcc.compiler.general.ChangeDefaultBitFieldUnsigned>True</avrgcc.compiler.general.ChangeDefaultBitFieldUnsigned>
  <avrgcc.compiler.symbols.DefSymbols>
    <ListValues>
      <Value>DEBUG</Value>
    </ListValues>
  </avrgcc.compiler.symbols.DefSymbols>
  <avrgcc.compiler.directories.IncludePaths>
    <ListValues>
      <Value>%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/include</Value>
    </ListValues>
  </avrgcc.compiler.directories.IncludePaths>
  <avrgcc.compiler.optimization.level>Optimize (-O1)</avrgcc.compiler.optimization.level>
  <avrgcc.compiler.optimization.PackStructureMembers>True</avrgcc.compiler.optimization.PackStructureMembers>
  <avrgcc.compiler.optimization.AllocateBytesNeededForEnum>True</avrgcc.compiler.optimization.AllocateBytesNeededForEnum>
  <avrgcc.compiler.optimization.DebugLevel>Default (-g2)</avrgcc.compiler.optimization.DebugLevel>
  <avrgcc.compiler.warnings.AllWarnings>True</avrgcc.compiler.warnings.AllWarnings>
  <avrgcc.linker.libraries.Libraries>
    <ListValues>
      <Value>libm</Value>
    </ListValues>
  </avrgcc.linker.libraries.Libraries>
  <avrgcc.assembler.general.IncludePaths>
    <ListValues>
      <Value>%24(PackRepoDir)/atmel/ATmega_DFP/1.3.300/include</Value>
    </ListValues>
  </avrgcc.assembler.general.IncludePaths>
  <avrgcc.assembler.debugging.DebugLevel>Default (-Wa,-g)</avrgcc.assembler.debugging.DebugLevel>
</AvrGcc>
    </ToolchainSettings>
  </PropertyGroup>
  <ItemGroup>
"""

cprojEpilogue = """
  </ItemGroup>
  <Import Project="$(AVRSTUDIO_EXE_PATH)//Vs//Compiler.targets" />
</Project>
"""

for file in os.listdir("./"):
	if file.endswith(".c"):
		sourceFiles.append(file)
	elif file.endswith(".h"):
		headerFiles.append(file)

cprojFile.write(cprojPreamble)

# Place Source Files First
for file in sourceFiles:
	cprojFile.write("<Compile Include=\"../")
	cprojFile.write(file)
	cprojFile.write("\">\n<SubType>compile</SubType>\n</Compile>\n")

# Place Header Files Second
for file in headerFiles:
	cprojFile.write("<Compile Include=\"../")
	cprojFile.write(file)
	cprojFile.write("\">\n<SubType>compile</SubType>\n</Compile>\n")

cprojFile.write(cprojEpilogue)
cprojFile.close()

print(" -- SUCCESS! FILES GENERATED -- ")
