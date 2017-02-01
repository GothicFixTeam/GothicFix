////////////////////////////////////////////////////////////////////////////////
//
//  GothicStarter - 2.6
//
//      Status: public domain
//

Der GothicStarter wurde mal eben runtergeschrieben - wobei insbesondere darauf
geachtet wurde, dass die resultierende Programmdatei so klein wie möglich ist.
Der Quellcode wurde weder aufgeräumt noch formatiert, da die Zeit dazu fehlte.
In diesem Paket sind Projekt-Dateien für die 'Borland Free Commandline Tools',
'Borland C++Builder', 'Bloodshed Dev-C++' und 'Microsoft Visual C++' enthalten
(es ist eine ganze Menge an Arbeit notwendig, um die C 'Standard-Bibliotheken'
und unter den verwendeten Entwicklungsumgebungen alle Warnungen los zu werden)
Ich habe versucht den Quellcode ANSI C -konform zu halten (was natürlich nicht
heisst, dass er keine Fehler enthalten kann/wird... :)
Fast alle Dateien (ausser dieser) wurden mit UNIX-Zeilenumbrüchen gespeichert.


May the source be with you,
Nico Bendlin <nicode@gmx.net>


[Files]
GothicStarter.c         C Source
GothicStarter.h         C Header
res\*                   Ressourcen (script/header, icon, manifest)
lib\*                   Standard-Bibliotheken-Ersatz für BCB und MSVC
bin\*                   Tools um die EXE-Datei zu schrumpfen (nicht enthalten)
bcc.bat                 Batch für die 'Free Commandline Tools'
bin.bat                 Batch für den Aufruf der EXE-Tools
GothicStarter.bcc       Makefile für 'Borland C++ Compiler' Version 5.5
GothicStarter.bpr       Projekt-Datei für 'Borland C++Builder' Version 6.0
GothicStarter.dev       Projekt-Datei für 'Bloodshed Dev-C++' Version 4.9.8
GothicStarter.dsp       Projekt-Datei für 'Microsoft Visual C++' Version 6.0
GothicStarter.vcproj    Projekt-Datei für 'Microsoft Visual C++' Version 8.0
