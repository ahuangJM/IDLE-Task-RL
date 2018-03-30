# IDLE-Task-RL
utilize the idle time on a cluster of personal computers to perform callaborative RL

### Dependencies ###  
'''
python -m pip install --upgrade pip
.\pip.exe install numpy
.\pip.exe install matplotlib
'''

### Set Up ###  
1. Create a task in Task Scheduler:  
    Actions  
        New  
            Program/script "C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe"
            Add Argument "powershell -executionpolicy bypass -File PATH\start.ps1"
