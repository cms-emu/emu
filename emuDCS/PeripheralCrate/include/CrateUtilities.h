#define CrateUtilities_h

#include <iostream>
#include <fstream>


#include "TestBeamCrateController.h"
#include "DAQMB.h"
#include "TMB.h"
#include "CCB.h"
#include "MPC.h"
#include "DDU.h"
#include "ALCTController.h"

class CrateUtilities {
  //
public:
  //
  CrateUtilities();
  CrateUtilities(TMB*);
  virtual ~CrateUtilities();
  //
  void CCBStartTrigger();
  void CFEBTiming();
  void PulseCFEB(int HalfStrip = -1, int CLCTInputs = 0x1f );
  void CFEBChamberScan();
  void PulseTestStrips();
  void ALCTTiming();
  void ALCTScanDelays();
  void ALCTChamberScan();
  void ALCTSVFLoad();
  int  TMBL1aTiming();
  int  FindBestL1aAlct();
  void PulseRandomALCT();
  int  FindWinner(int);
  int  FindALCTvpf();
  int  FindTMB_L1A_delay(int,int);
  int  FindALCT_L1A_delay(int,int);
  void Automatic();
  int  AdjustL1aLctDMB();
  void InitStartSystem();
  void InjectMPCData() ;
  void ALCT_phase_analysis(int rxtxtiming[13][13]);
  //
  bool UseCosmic ;
  bool UsePulsing ;
  //
  int BestCCBDelaySetting ;
  float CFEBMean[5];
  int TMB_L1a_timing ;
  int Find_ALCT_L1a_delay;
  int ALCT_L1a_delay ;
  int ALCTvpf;
  int beginning;
  //
  inline void SetTMB(TMB* myTMB) {thisTMB = myTMB; }
  inline void SetDMB(DAQMB* myDMB) {thisDMB = myDMB; }
  inline void SetCCB(CCB* myCCB) {thisCCB = myCCB; }
  inline void SetALCT(ALCTController* myAlct) {alct = myAlct; }
  inline int  GetALCTrxPhase() { return ALCTrxPhase_; }
  inline int  GetALCTtxPhase() { return ALCTtxPhase_; }
  inline int  GetCFEBrxPhase(int CFEB) {return CFEBrxPhase_[CFEB]; }
  inline int  GetCFEBStripScan(int CFEB, int Strip){ return CFEBStripScan_[CFEB][Strip]; }
  inline int  GetALCTWireScan(int Wire){ return ALCTWireScan_[Wire]; }
  inline int  GetTMBL1aTiming(){ return TMBL1aTiming_; }
  inline int  GetALCTvpf(){ return ALCTvpf_; }
  inline int  GetBestALCTL1aDelay(){ return BestALCTL1aDelay_; }
  inline int  GetALCTL1aDelay(){ return ALCTL1aDelay_; }
  //
private:
  //
  TestBeamCrateController tbController;
  //
  TMB * thisTMB ;
  DAQMB* thisDMB ;
  CCB* thisCCB ;
  ALCTController *alct ;
  MPC * thisMPC;
  //
  int ALCTrxPhase_, ALCTtxPhase_;
  int TMBL1aTiming_;
  int ALCTvpf_;
  int BestALCTL1aDelay_;
  int ALCTL1aDelay_;
  int CFEBrxPhase_[5];
  int CFEBStripScan_[5][32];
  int ALCTWireScan_[112];
  int Npulses_;
  //
};
