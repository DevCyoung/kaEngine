﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Runtime.Versioning;
using System.Security.Cryptography.X509Certificates;
using System.Text;



public class MyProgram
{
    static string SHARP_INCLUDE = "#include";
    //static string SHARP_DEFINE= "#define";
    static string BEGIN_ENGINE_NAMESPACE = "namespace engine\n{\n";
    static string END_ENGINE_NAMESPACE = "}\n";
    static string RESOURCE_PATH = "";

    public static void Main(string[] args)
    {
        //string path = @"C:\Users\tkdlq\Desktop\assort\DirectX2D_Engine\Output\bin\resource";
        //string targetPath = @"C:\Users\tkdlq\Desktop\assort\DirectX2D_Engine\Output\bin";

        

        string path = @"";
        string targetPath = @"";

        if (args.Length == 2)
        {            
            path += args[0];
            targetPath += args[1];

            RESOURCE_PATH = path;

            if (targetPath[targetPath.Length - 1] != '\\')
            {
                targetPath += '\\';
            }

            string resourcePath = path;

            string[] resourceDirectorys = Directory.GetDirectories(resourcePath);
            if (null == resourceDirectorys)
            {
                Console.WriteLine("resourceDirectorys is null");
                return;
            }

            

            foreach (string resDirectory in resourceDirectorys)
            {
                string enumType = GetFileName(resDirectory);
                

                List<string> enumNames = new List<string>();
                List<string> enumFilePath = new List<string>();

                MakeEnumNames(resDirectory, enumNames, enumFilePath, "");

                string enumHeader = MakeEnumNumHeader(enumType, enumNames);

                string enumHeaderPath =
                   targetPath + "EnumResourceType" + enumType + ".h";               

                StreamWriter enumHearderWriter = new StreamWriter(
                new FileStream(enumHeaderPath
                , FileMode.Create)
                , Encoding.UTF8);
                enumHearderWriter.Write(enumHeader);
                enumHearderWriter.Close();



                string enumCpp = MakeEnumCpp(enumType, enumFilePath);

                string enumCppPath =
                    targetPath + "EnumResourceType" + enumType + ".cpp";

                StreamWriter enumCppWirter = new StreamWriter(
                new FileStream(enumCppPath
                , FileMode.Create)
                , Encoding.UTF8);
                enumCppWirter.Write(enumCpp);
                enumCppWirter.Close();








            }

            //EnumResourceEna
        }
        else
        {
            Console.WriteLine("need 2 arguments");
        }
        
    }

    public static string[] GetDirectories(string resourcePath)
    {
        string[] directorys = Directory.GetDirectories(resourcePath);

        foreach (string directory in directorys)
        {
            GetDirectories(directory);
        }

        string[] fileNames = Directory.GetFiles(resourcePath);

        return directorys;
    }

    public static string GetFileName(string path)
    {
        string[] split = path.Split('\\');
        string fileName = split[split.Length - 1];

        return fileName;
    }

    public static void MakeEnumNames(string resDirectory, 
        List<string> enumNames,
        List<string> enumFilePath, 
        string recursiveEnumName)
    {
        string[] directorys = Directory.GetDirectories(resDirectory);

        foreach (string directory in directorys)
        {
            string prev = recursiveEnumName;

            recursiveEnumName += GetFileName(directory) + "_";
            MakeEnumNames(directory, enumNames, enumFilePath, recursiveEnumName);

            recursiveEnumName = prev;
        }

        string[] fileNames = Directory.GetFiles(resDirectory);
        

        

        foreach (string fileName in fileNames)
        {
            string perfactEnumName = recursiveEnumName + Path.GetFileNameWithoutExtension(
                GetFileName(fileName));
            enumNames.Add(perfactEnumName);
            
            string resourceBaseFileName = fileName.Replace(resDirectory, "");
            resourceBaseFileName = resourceBaseFileName.Replace("\\", "\\\\");
            enumFilePath.Add(fileName.Replace(RESOURCE_PATH, "").Replace("\\", "\\\\"));

        }
    }
    

    public static string MakeEnumNumHeader(string enumType, List<string> enumNames)
    {
        string header = "";

        header += "#pragma once\n\n";
        //header += "#include <string>\n";

        header += "";
        header += "namespace engine\n{\n";
        header += "\tenum class " + "eRes" + enumType + "\n";
        header += "\t{\n";

        foreach (string enumName in enumNames)
        {
            header += "\t\t" + enumName + ",\n";
        }
        header += "\t" + "\tEnd\n";
        header += "\t};\n\n";
        
        if (enumNames.Count > 0)
        {
            header += $"\tconst wchar_t* EnumResourcePath(eRes{enumType} type);\n";
        }        
        
        header += "}\n";

        return header;
    }

    //enum to Path
    public static string MakeEnumCpp(string enumType, List<string> relativePaths)
    {
        string cpp = "";
        string eResEnumType = $"eRes{enumType}";
        string enumResourcePathArray = $"{eResEnumType}Path";
        

        cpp += $"{SHARP_INCLUDE} \"pch.h\"\n";
        cpp += $"{SHARP_INCLUDE} \"EnumResourceType{enumType}.h\"\n";
        cpp += "\n";
        cpp += BEGIN_ENGINE_NAMESPACE;
        cpp += "";

        //const wchar
        if (relativePaths.Count > 0)
        {
            cpp += $"\tconst wchar_t* {enumResourcePathArray}[static_cast<UINT>({eResEnumType}::End)]\n";
            cpp += "\t{\n";
            foreach (string relativePath in relativePaths)
            {
                //리소스 하위로가져온다.
                cpp += $"\t\tL\"{relativePath}\",\n";
            }
            cpp += "\t};\n";
            cpp += "\n";
            cpp += $"\tconst wchar_t* EnumResourcePath(eRes{enumType} type)\n";
            cpp += "\t{\n";
            cpp += $"\t\treturn {enumResourcePathArray}[static_cast<UINT>(type)];\n";
            cpp += "\t}\n";
        }
        
        cpp += END_ENGINE_NAMESPACE;

        //const char* EnumResourceToString(COMPONENT_TYPE _type) { return COMPONENT_TYPE_LPCSTR[(UINT)_type]; }
        //const wchar_t* EnumResourceToWString(COMPONENT_TYPE _type) { return COMPONENT_TYPE_LPCWSTR[(UINT)_type]; }

        return cpp;
    }


    
}
////COMPONENT_TYPE
//extern const char* COMPONENT_TYPE_LPCSTR[(UINT)COMPONENT_TYPE::SCRIPT + 1]
//{
//	"TRANSFORM",
//	"COLLIDER2D",
//	"COLLIDER3D",
//	"RIGIDBODY2D",
//	"ANIMATOR2D",
//	"ANIMATOR3D",
//	"LIGHT2D",
//	"LIGHT3D",
//	"CAMERA",
//	"MESHRENDER",
//	"PARTICLESYSTEM",
//	"TILEMAP",
//	"LANDSCAPE",
//	"DECAL",
//	"LINECOLLIDER2DS",
//	"END",
//	"SCRIPT",
//};