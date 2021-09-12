*** Settings ***
Documentation    TiN Project
Library    OperatingSystem
Library    Dialogs
Library    python/Keywords.py

*** Variables ***


*** Test Cases ***


TC Upload Software
    Check If Software Is Available
    Check If Board Is Connected
    Upload Software
    Check If Board Is Connected

TC Req Switch Output Test
    Set Input GPIO All
    Send Req Switch Output
    Check If All GPIO Are Inputs

TC Send Req Set All High
    Set Input GPIO All
    Send Req Set All High
    Check Input GPIO Value All High
    Check If All GPIO Are Inputs

TC Send Req Set All Low
    Set Input GPIO All
    Send Req Set All Low
    Check Input GPIO Value All Low
    Check If All GPIO Are Inputs

TC Send Req Switch Input
    Set Input GPIO All
    Send Req Switch Input
    Check If All GPIO Are Inputs

TC Set Output GPIO All Low
    Set Output GPIO All Low
    Check If All GPIO Are Outputs
    Send Req Input State All Low

TC Set Output GPIO All High
    Set Output GPIO All High
    Check If All GPIO Are Outputs
    Send Req Input State All High


*** Keywords ***


Check If All GPIO Are Inputs
    Check Pin State    in

Check If All GPIO Are Outputs
    Check Pin State    out

Set Output GPIO All High
    Set Output GPIO    ${1048575}

Set Output GPIO All Low
    Set Output GPIO    ${0}

Set Output GPIO Sequence 1
    Set Output GPIO    ${3}

Check Input GPIO Value All High
    Check Input GPIO Value    ${1048575}

Check Input GPIO Value All Low
    Check Input GPIO Value    ${0}

Send Req Set All High
    ${result}    Map Bin to String To Send    ${1048575}
    ${str1}    Catenate    SEPARATOR=    REQ_SET_    ${result}    \n
    ${str2}    Catenate    SEPARATOR=    ACK_SET_    ${result}
    Send String Via UART And Wait For Response    ${str1}    ${str2}

Send Req Set All Low
    ${result}    Map Bin to String To Send    ${0}
    ${str1}    Catenate    SEPARATOR=    REQ_SET_    ${result}    \n
    ${str2}    Catenate    SEPARATOR=    ACK_SET_    ${result}
    Send String Via UART And Wait For Response    ${str1}    ${str2}

Send Req Switch Input
    Send String Via UART And Wait For Response    REQ_SWITCH_INPUT\n    ACK_SWITCH_INPUT

Send Req Switch Output
    Send String Via UART And Wait For Response    REQ_SWITCH_OUTPUT\n    ACK_SWITCH_OUTPUT

Send Req Input State All Low
    ${result}    Map Bin to String To Send    ${0}
    ${str1}    Catenate    SEPARATOR=    ACK_INPUT_STATE_    ${result}
    Send String Via UART And Wait For Response    REQ_INPUT_STATE\n    ${str1}

Send Req Input State All High
    ${result}    Map Bin to String To Send    ${1048575}
    ${str1}    Catenate    SEPARATOR=    ACK_INPUT_STATE_    ${result}
    Send String Via UART And Wait For Response    REQ_INPUT_STATE\n    ${str1}



