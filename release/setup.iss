; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Robot manager"
#define MyAppVersion "1.0"
#define MyAppPublisher "Rhoban"
#define MyAppURL "http://metabot.cc/"
#define MyAppExeName "RobotManager.exe"

[Setup]                                                                        
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{42C8C573-260A-4340-981F-893CBCE92F66}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\RobotManager
DisableDirPage=yes
DefaultGroupName=Robot
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Dirs]
Name: "{app}\platforms"
Name: "{app}\iconengines"
Name: "{app}\imageformats"
Name: "{app}\bearer"
Name: "{app}\translations"

[Files]
Source: "RobotManager\fr.qm"; DestDir: "{app}"; DestName: "messages.qm"; Languages: french
Source: "RobotManager\en.qm"; DestDir: "{app}"; DestName: "messages.qm"; Languages: english
Source: "RobotManager\RobotManager.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "RobotManager\*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "RobotManager\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion
Source: "RobotManager\iconengines\*"; DestDir: "{app}\iconengines\"; Flags: ignoreversion
Source: "RobotManager\imageformats\*"; DestDir: "{app}\imageformats\"; Flags: ignoreversion
Source: "RobotManager\translations\*"; DestDir: "{app}\translations\"; Flags: ignoreversion
Source: "RobotManager\bearer\*"; DestDir: "{app}\bearer\"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

