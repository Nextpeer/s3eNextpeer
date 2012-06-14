#include "s3eNextpeer.h"
#include "s3eDevice.h"
#include "s3ePointer.h"
#include "s3eSurface.h"
#include "s3eTimer.h"
#include "IwDebug.h"

// Callbacks
static int32 didTournamentStartWithDetails(void* systemData, void* userData)
{
    s3eDebugPrint(0, 60, "Tournament started", 0);
	//s3eDebugPrintf(0, 60, 1, "Started tournament with id %s [%d seconds]", details->m_tournamentUuid, details->m_tournamentSeconds);
    
    return 0;
}

static int32 didTournamentEnd(void* systemData, void* userData)
{
	s3eDebugPrintf(0, 90, 1, "Tournament end callback called");
    
    return 0;
}

S3E_MAIN_DECL int main()
{
    int screen_presses = 0;

    uint32 score = 0;
    
    if (s3eNextpeerAvailable()) {   
        s3eDebugPrint(0, 30, "Nextpeer will be loaded", 0);
        
        // Register for callbacks
        s3eNextpeerRegisterCallback(S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_START, &didTournamentStartWithDetails, NULL);
        s3eNextpeerRegisterCallback(S3E_NEXTPEER_CALLBACK_DID_TOURNAMENT_END, &didTournamentEnd, NULL);
        
        // Call Nextpeer's init function
        s3eNextpeerInitWithProductKey("e59d317f2e26de5dc78ad83539adfe8af2ba319b");

        // Launch Nextpeer's dashboard
        s3eNextpeerLaunchDashboard();
    }
    else {
        s3eDebugPrint(0, 30, "Nextpeer is unavailable", 0);
    }
    
    while (!s3eDeviceCheckQuitRequest())
    {
        if (s3eNextpeerIsCurrentlyInTournament()) {
            if (score++ % 60 == 0) {
                s3eNextpeerReportScoreForCurrentTournament(score);
            }
        }
        
        s3eDeviceYield(0);
        s3ePointerUpdate();
        //s3eDebugPrint(0,30,"Status bar test application", 0);
        s3eSurfaceShow();
    }

    return 0;
}