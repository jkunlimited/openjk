;======================================================
;            Inno Setup Installer Script
;                    env_setup
;
;------------------------------------------------------
; Author:   Fnuki
; Date:     2020-04-18 20:39
; Version:  0.1
;------------------------------------------------------
;
; First attempt to create an installer for this project
; to no longer manually copy and paste files
;======================================================


; Build configuration
#define JKUBuildConfiguration GetEnv("JKU_BUILD_CONFIGURATION")
#if JKUBuildConfiguration == ""
#pragma error "Invalid build configuration specified"
#endif

#define JKUBuildConfigDisplayName = LowerCase(JKUBuildConfiguration)

; Build directory
#define JKUBuildDirectory GetEnv("JKU_BUILD_DIRECTORY")
#if JKUBuildDirectory == ""
#pragma error "Invalid build directory specified"
#endif