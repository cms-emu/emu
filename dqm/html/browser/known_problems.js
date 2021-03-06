var KNOWN_PROBLEMS = { "run": "csc_00124357_Monitor", "genDate": "2010-02-19 11:12:00 CET", "report":
[
{"objID": "ME+1/1/17", "name": "ME+1/1/17", "list": [
        {"testID": "CSC_ALCT_NO_ANODE_DATA", "scope": "CSC", "descr": "ALCT No Anode Data: AFEB1 Layer1", "severity": "3", "obj": "AFEB1 Layer1"},
        {"testID": "CSC_ALCT_NO_ANODE_DATA", "scope": "CSC", "descr": "ALCT No Anode Data: AFEB1 Layer2", "severity": "3", "obj": "AFEB1 Layer2"}
]},
{"objID": "ME+1/2/03", "name": "ME+1/2/03", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB5 Layer5 Ch#1", "severity": "1", "obj": "CFEB5 Layer5 Ch#1"}
]},
{"objID": "ME+1/2/13", "name": "ME+1/2/13", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME+1/2/15", "name": "ME+1/2/15", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB1 DAV 0.000%", "severity": "3", "obj": "CFEB1"}
]},
{"objID": "ME+1/2/18", "name": "ME+1/2/18", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},

{"objID": "ME+1/2/21", "name": "ME+1/2/21", "list": [
        {"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB No SCA Data: CFEB2", "severity": "3", "obj": "CFEB2"},
	{"testID": "CSC_CFEB_NO_SCA_DATA", "scope": "CSC", "descr": "CFEB No SCA Data: CFEB2", "severity": "3", "obj": "CFEB2"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB2", "severity": "3", "obj": "CFEB2"},
        {"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB2", "severity": "3", "obj": "CFEB2"},
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},

{"objID": "ME+1/2/26", "name": "ME+1/2/26", "list": [ 
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"},
	{"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB5 Layer6 Ch#9", "severity": "1", "obj": "CFEB5 Layer6 Ch#9"}
]}, 
{"objID": "ME+1/2/28", "name": "ME+1/2/28", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"}   
]},
{"objID": "ME+1/2/31", "name": "ME+1/2/31", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB5 DAV 3.000%", "severity": "2", "obj": "CFEB5"}
]},
{"objID": "ME+1/3/11", "name": "ME+1/3/11", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"},
	{"testID": "CSC_WITH_BWORDS", "scope": "CSC", "descr": "CFEB B-Words because of CFEB3", "severity": "3", "obj": "CFEB"}
]},
{"objID": "ME+1/3/22", "name": "ME+1/3/22", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB1 DAV 7.000%", "severity": "2", "obj": "CFEB1"},
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB1 Layer6 Ch#1", "severity": "1", "obj": "CFEB1 Layer6 Ch#1"}
]},
{"objID": "ME+1/3/26", "name": "ME+1/3/26", "list": [
	{"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB3 ( < 20.0% from average)", "severity": "2", "obj": "CFEB3"},
	{"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB3 ( < 20.0% from average)", "severity": "2", "obj": "CFEB3"}
]},
{"objID": "ME+2/1/01", "name": "ME+2/1/01", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"},
	{"testID": "CSC_CFEB_SCA_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy SCA channel: CFEB3 Layer3 Ch#4 (occupancy  > average)", "severity": "1", "obj": "CFEB3 Layer3 Ch#4"},
	{"testID": "CSC_CFEB_SCA_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy SCA channel: CFEB3 Layer5 Ch#5 (occupancy  > average)", "severity": "1", "obj": "CFEB3 Layer5 Ch#5"}
]},
{"objID": "ME+2/1/03", "name": "ME+2/1/03", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB4 DAV", "severity": "2", "obj": "CFEB4"}
]},
{"objID": "ME+2/2/04", "name": "ME+2/2/04", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB1 Layer2 Ch#2", "severity": "1", "obj": "CFEB1 Layer2 Ch#2"}
]},
{"objID": "ME+2/2/05", "name": "ME+2/2/05", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB1 DAV", "severity": "2", "obj": "CFEB1"}
]},
{"objID": "ME+2/2/13", "name": "ME+2/2/13", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB4 Layer1 Ch#2", "severity": "1", "obj": "CFEB4 Layer1 Ch#2"}
]},
{"objID": "ME+2/2/14", "name": "ME+2/2/14", "list": [
        {"testID": "CSC_WITHOUT_ALCT", "scope": "CSC", "descr": "No ALCT Data: 100.0%", "severity": "4", "obj": "ALCT"},
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB20 Layer4", "severity": "2", "obj": "AFEB20 Layer4"},
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB23 Layer4", "severity": "2", "obj": "AFEB23 Layer4"}
]},
{"objID": "ME+2/2/15", "name": "ME+2/2/15", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB5 DAV", "severity": "2", "obj": "CFEB5"}
]},
{"objID": "ME+2/2/19", "name": "ME+2/2/19", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME+2/2/20", "name": "ME+2/2/20", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"}
]},
{"objID": "ME+2/2/22", "name": "ME+2/2/22", "list": [
        {"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB2 Layer3 ( < 20.0% from average)", "severity": "2", "obj": "CFEB2 Layer3"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB2 Layer3 ( < 20.0% from average)", "severity": "2", "obj": "CFEB2 Layer3"}
]},
{"objID": "ME+2/2/30", "name": "ME+2/2/30", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},
{"objID": "ME+2/2/35", "name": "ME+2/2/35", "list": [
	{"testID": "CSC_NO_HV_SEGMENT", "scope": "CSC", "descr": "No HV: Segment5 Layer3", "severity": "2", "obj": "Segment5 Layer3"}
]},
{"objID": "ME+3/1/07", "name": "ME+3/1/07", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV 6.000%", "severity": "2", "obj": "CFEB3"},
	{"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB3 (< 20.0% from average)", "severity": "2", "obj": "CFEB3"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB3 (< 20.0% from average)", "severity": "2", "obj": "CFEB3"},
        {"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB3", "severity": "3", "obj": "CFEB3"}
]},
{"objID": "ME+3/1/08", "name": "ME+3/1/08", "list": [
	{"testID": "CSC_NO_HV_SEGMENT", "scope": "CSC", "descr": "No HV: Segment3 Layer5", "severity": "2", "obj": "Segment3 Layer5"}
]},
{"objID": "ME+3/1/10", "name": "ME+3/1/10", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB2 DAV", "severity": "2", "obj": "CFEB2"}
]},
{"objID": "ME+3/1/11", "name": "ME+3/1/11", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV", "severity": "2", "obj": "CFEB3"},
	{"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB3 (< 20.0% from average)", "severity": "2", "obj": "CFEB3"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB3 (< 20.0% from average)", "severity": "2", "obj": "CFEB3"},
        {"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB3", "severity": "3", "obj": "CFEB3"},
	{"testID": "CSC_CFEB_SCA_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy SCA channel: CFEB1 Layer1 Ch#4 (occupancy 3.2 times > average)", "severity": "2", "obj": "CFEB1 Layer1 Ch#4"}
]},
{"objID": "ME+3/2/01", "name": "ME+3/2/01", "list": [
	{"testID": "CSC_NO_HV_SEGMENT", "scope": "CSC", "descr": "No HV: Segment5 Layer5", "severity": "2", "obj": "Segment5 Layer5"}
]},
{"objID": "ME+3/2/07", "name": "ME+3/2/07", "list": [
	{"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB2 Layer2 Ch#16", "severity": "1", "obj": "CFEB2 Layer2 Ch#16"}
]},
{"objID": "ME+3/2/19", "name": "ME+3/2/19", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME+3/2/29", "name": "ME+3/2/29", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB4 DAV 0.000%", "severity": "3", "obj": "CFEB4"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB4 (< 20% threshold)", "severity": "2", "obj": "CFEB4"},
	{"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB4 (< 20.0% from average)", "severity": "2", "obj": "CFEB4"},
	{"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB4" , "severity": "3", "obj": "CFEB4"}
]},
{"objID": "ME+3/2/30", "name": "ME+3/2/30", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"},
	{"testID": "CSC_CFEB_COMPARATORS_NOISY", "scope": "CSC", "descr": "CFEB Hot/Noisy CFEB Comparators: CFEB1 Layer4", "severity": "3", "obj": "CFEB1 Layer4"},
        {"testID": "CSC_CFEB_COMPARATORS_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy Comparator channels CFEB1 Layer4 HStrip", "severity": "2", "obj": "CFEB1 Layer4"}
]},
{"objID": "ME+4/1/07", "name": "ME+4/1/07", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME+4/1/09", "name": "ME+4/1/09", "list": [ 
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB5 Layer4 Ch#7", "severity": "1", "obj": "CFEB5 Layer4 Ch#7"}
]},
{"objID": "ME+4/1/14", "name": "ME+4/1/14", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB2 Layer4 Ch#3", "severity": "1", "obj": "CFEB2 Layer4 Ch#3"}
]},
{"objID": "ME+4/1/15", "name": "ME+4/1/15", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME+4/2/09", "name": "ME+4/2/09", "list": [
	{"testID": "CSC_CLCT_TIMING", "scope": "CSC", "descr": "CLCT Timing problem (CLCT0 BXN - L1A BXN) RMS >2.11", "severity": "3", "obj": "CLCT0"}
]},
{"objID": "ME+4/2/10", "name": "ME+4/2/10", "list": [
	{"testID": "CSC_CLCT_TIMING", "scope": "CSC", "descr": "CLCT Timing problem (CLCT0 BXN - L1A BXN) RMS >2.11", "severity": "3", "obj": "CLCT0"}
]},
{"objID": "ME+4/2/11", "name": "ME+4/2/11", "list": [
	{"testID": "CSC_CLCT_TIMING", "scope": "CSC", "descr": "CLCT Timing problem (CLCT0 BXN - L1A BXN) RMS >2.11", "severity": "3", "obj": "CLCT0"}
]},
{"objID": "ME+4/2/12", "name": "ME+4/2/12", "list": [
	{"testID": "CSC_CLCT_TIMING", "scope": "CSC", "descr": "CLCT Timing problem (CLCT0 BXN - L1A BXN) RMS >2.11", "severity": "3", "obj": "CLCT0"}
]},
{"objID": "ME+4/2/13", "name": "ME+4/2/13", "list": [
	{"testID": "CSC_CLCT_TIMING", "scope": "CSC", "descr": "CLCT Timing problem (CLCT0 BXN - L1A BXN) RMS >2.11", "severity": "3", "obj": "CLCT0"}
]},
{"objID": "ME+4/2/32", "name": "ME+4/2/32", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB1 DAV 0.000%", "severity": "3", "obj": "CFEB1"}
]},
{"objID": "ME+2/1/12", "name": "ME+2/1/12", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB4 DAV 0.000%", "severity": "3", "obj": "CFEB4"}
]},
{"objID": "ME-1/2/10", "name": "ME-1/2/10", "list": [
	{"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB21 Layer6", "severity": "2", "obj": "AFEB21 Layer6"},
	{"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB24 Layer6", "severity": "2", "obj": "AFEB24 Layer6"},
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB13 Layer2", "severity": "2", "obj": "AFEB13 Layer2"},
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB16 Layer2", "severity": "2", "obj": "AFEB16 Layer2"}
]},
{"objID": "ME-1/2/22", "name": "ME-1/2/22", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"}
]},
{"objID": "ME-1/2/33", "name": "ME-1/2/33", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB1 DAV", "severity": "2", "obj": "CFEB1"},
        {"testID": "CSC_CFEB_NO_SCA_DATA", "scope": "CSC", "descr": "CFEB No SCA Data: CFEB1", "severity": "3", "obj": "CFEB1"},
        {"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB1", "severity": "3", "obj": "CFEB1"}
]},
{"objID": "ME-1/3/03", "name": "ME-1/3/03", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB1 DAV 0.000%", "severity": "3", "obj": "CFEB1"}
]},
{"objID": "ME-1/3/12", "name": "ME-1/3/12", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV", "severity": "2", "obj": "CFEB3"}
]},
{"objID": "ME-1/3/13", "name": "ME-1/3/13", "list": [
        {"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB2 (< 20.0% from average)", "severity": "2", "obj": "CFEB2"},
]},
{"objID": "ME-1/3/30", "name": "ME-1/3/30", "list": [
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB7 Layer2", "severity": "2", "obj": "AFEB7 Layer2"},
        {"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB10 Layer2", "severity": "2", "obj": "AFEB10 Layer2"}
]},
{"objID": "ME-1/3/31", "name": "ME-1/3/31", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},
{"objID": "ME-2/1/06", "name": "ME-2/1/06", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB1 DAV 0.000%", "severity": "3", "obj": "CFEB1"}
]},
{"objID": "ME-2/1/17", "name": "ME-2/1/17", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB3 Layer2 Ch#1", "severity": "1", "obj": "CFEB3 Layer2 Ch#1"},
	 {"testID": "CSC_WITHOUT_ALCT", "scope": "CSC", "descr": "No ALCT Data: (because of Hot CFEB5)", "severity": "4", "obj": "ALCT"},
        {"testID": "CSC_WITHOUT_CLCT", "scope": "CSC", "descr": "No CLCT Data: (because of Hot CFEB5)", "severity": "4", "obj": "CLCT"},
        {"testID": "CSC_HOT_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Hot: CFEB5 DAV ( > 60% )", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME-2/2/03", "name": "ME-2/2/03", "list": [
        {"testID": "CSC_WITHOUT_ALCT", "scope": "CSC", "descr": "No ALCT Data: 100.0%", "severity": "4", "obj": "ALCT"},
        {"testID": "CSC_WITHOUT_CLCT", "scope": "CSC", "descr": "No CLCT Data: 100.0%", "severity": "4", "obj": "CLCT"},
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},
{"objID": "ME-2/2/05", "name": "ME-2/2/05", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB4 Layer2 Ch#13", "severity": "1", "obj": "CFEB4 Layer2 Ch#13"}
]},
{"objID": "ME-2/2/07", "name": "ME-2/2/07", "list": [
        {"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB3 Layer3 (< 20.0% from average)", "severity": "2", "obj": "CFEB3 Layer3"}
]},
{"objID": "ME-2/2/11", "name": "ME-2/2/11", "list": [
	{"testID": "CSC_ALCT_AFEB_NOISY", "scope": "CSC", "descr": "Noisy Anodes Segment: AFEB15 Layer5", "severity": "2", "obj": "AFEB15 Layer5"}
]},
{"objID": "ME-2/2/27", "name": "ME-2/2/27", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB5 DAV", "severity": "2", "obj": "CFEB5"}
]},
{"objID": "ME-2/2/31", "name": "ME-2/2/31", "list": [
	{"testID": "CSC_CFEB_SCA_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy SCA channel: CFEB2 Layer1 Ch#16 (occupancy > average)", "severity": "1", "obj": "CFEB2 Layer1 Ch#16"}
]},
{"objID": "ME-2/2/32", "name": "ME-2/2/32", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB1 Layer5 Ch#1", "severity": "1", "obj": "CFEB1 Layer5 Ch#1"}
]},
{"objID": "ME-3/1/03", "name": "ME-3/1/03", "list": [
	{"testID": "CSC_WITHOUT_ALCT", "scope": "CSC", "descr": "No ALCT Data: 100.0%", "severity": "4", "obj": "ALCT"},
        {"testID": "CSC_CFEB_SCA_LOW_EFF", "scope": "CSC", "descr": "CFEB Low SCA Efficiency: CFEB3 Layer2 ( < 20.0% from average)", "severity": "2", "obj": "CFEB3 Layer2"},
        {"testID": "CSC_CFEB_COMPARATORS_LOW_EFF", "scope": "CSC", "descr": "CFEB Low Comparators Efficiency: CFEB3 Layer2 ( < 20.0% from avierage)", "severity": "2", "obj": "CFEB3 Layer2"},
        {"testID": "CSC_CFEB_NO_SCA_DATA", "scope": "CSC", "descr": "CFEB No SCA Data: CFEB3 Layer2", "severity": "3", "obj": "CFEB3 Layer2"},
        {"testID": "CSC_CFEB_NO_COMPARATORS_DATA", "scope": "CSC", "descr": "CFEB No Comparators Data: CFEB3 Layer2", "severity": "3", "obj": "CFEB3 Layer2"}
]},
{"objID": "ME-3/1/09", "name": "ME-3/1/09", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB4 DAV 0.000%", "severity": "3", "obj": "CFEB4"}
]},
{"objID": "ME-3/1/11", "name": "ME-3/1/11", "list": [
        {"testID": "CSC_CFEB_COMPARATORS_NOISY", "scope": "CSC", "descr": "CFEB Hot/Noisy CFEB Comparators: CFEB4 Layer2 ( > 2.5 times from average)", "severity": "3", "obj": "CFEB4 Layer2"},
        {"testID": "CSC_CFEB_COMPARATORS_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy Comparator channel: CFEB4 Layer2 HStrip110 (occupancy > average)", "severity": "2", "obj": "CFEB4 Layer2 HStrip110"},
        {"testID": "CSC_CFEB_COMPARATORS_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy Comparator channel: CFEB4 Layer2 HStrip111 (occupancy > average)", "severity": "2", "obj": "CFEB4 Layer2 HStrip111"},
        {"testID": "CSC_CFEB_COMPARATORS_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy Comparator channel: CFEB4 Layer2 HStrip112 (occupancy > average)", "severity": "2", "obj": "CFEB4 Layer2 HStrip112"},
        {"testID": "CSC_CFEB_COMPARATORS_NOISY_CHANNEL", "scope": "CSC", "descr": "CFEB Hot/Noisy Comparator channel: CFEB4 Layer2 HStrip113 (occupancy > average)", "severity": "2", "obj": "CFEB4 Layer2 HStrip113"}
]},
{"objID": "ME-3/1/13", "name": "ME-3/1/13", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV", "severity": "2", "obj": "CFEB3"}
]},
{"objID": "ME-3/1/15", "name": "ME-3/1/15", "list": [ 
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB2 DAV", "severity": "2", "obj": "CFEB2"}
]},
{"ObjID": "ME-3/1/16", "name": "ME-3/1/16", "list": [
	{"testID": "CSC_NO_HV_SEGMENT", "scope": "CSC", "descr": "No HV: Segment3 Layer4", "severity": "2", "obj": "Segment3 Layer4"}
]},
{"objID": "ME-3/2/03", "name": "ME-3/2/03", "list": [
	{"testID": "CSC_NO_HV_SEGMENT", "scope": "CSC", "descr": "No HV: Segment1 Layer5", "severity": "2", "obj": "Segment1 Layer5"}
]},
{"objID": "ME-3/2/06", "name": "ME-3/2/06", "list": [ 
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV", "severity": "2", "obj": "CFEB3"}
]},
{"objID": "ME-3/2/15", "name": "ME-3/2/15", "list": [
        {"testID": "CSC_CFEB_SCA_DEAD_CHANNEL", "scope": "CSC", "descr": "Dead SCA channel: CFEB4 Layer6 Ch#16", "severity": "1", "obj": "CFEB4 Layer6 Ch#16"}
]},
{"objID": "ME-3/2/20", "name": "ME-3/2/20", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB4 DAV 0.000%", "severity": "3", "obj": "CFEB4"}
]},
{"objID": "ME-3/2/30", "name": "ME-3/2/30", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB1 DAV", "severity": "2", "obj": "CFEB1"},
]},
{"objID": "ME-4/1/01", "name": "ME-4/1/01", "list": [
	{"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB3 DAV", "severity": "2", "obj": "CFEB3"}
]},
{"objID": "ME-4/1/09", "name": "ME-4/1/09", "list": [
	{"testID": "CSC_ALCT_NO_ANODE_DATA", "scope": "CSC", "descr": "ALCT Low Anode Efficiency: AFEB25 Layer2", "severity": "2", "obj": "AFEB25 Layer2"},
	{"testID": "CSC_ALCT_NO_ANODE_DATA", "scope": "CSC", "descr": "ALCT Low Anode Efficiency: AFEB31 Layer2", "severity": "2", "obj": "AFEB31 Layer2"},
	{"testID": "CSC_ALCT_NO_ANODE_DATA", "scope": "CSC", "descr": "ALCT Low Anode Efficiency: AFEB26 Layer4", "severity": "2", "obj": "AFEB26 Layer4"}
]},
{"objID": "ME-4/1/11", "name": "ME-4/1/11", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB5 DAV 0.000%", "severity": "3", "obj": "CFEB5"}
]},
{"objID": "ME-4/1/14", "name": "ME-4/1/14", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"}
]},
{"objID": "ME-4/1/15", "name": "ME-4/1/15", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB5 DAV", "severity": "2", "obj": "CFEB5"}
]},
{"objID": "ME-4/2/01", "name": "ME-4/2/01", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB3 DAV 0.000%", "severity": "3", "obj": "CFEB3"}
]},
{"objID": "ME-4/2/14", "name": "ME-4/2/14", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Dead: CFEB2 DAV 0.000%", "severity": "3", "obj": "CFEB2"}
]},
{"objID": "ME-4/2/34", "name": "ME-4/2/34", "list": [
        {"testID": "CSC_WITH_LOW_CFEB_DAV_EFF", "scope": "CSC", "descr": "CFEB Low efficiency: CFEB5 DAV", "severity": "2", "obj": "CFEB5"}
]}
]
};
