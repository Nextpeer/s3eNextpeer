/*
 * Copyright (C) 2001-2011 Ideaworks3D Ltd.
 * All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Ideaworks Labs.
 * This file consists of source code released by Ideaworks Labs under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
#ifndef S3E_EXT_NEXTPEER_H
#define S3E_EXT_NEXTPEER_H

#include <s3eTypes.h>

#define S3E_NEXTPEER_STRING_MAX_1 50

/**
 * Structure to hold tournament info for callbacks. For now holds only the UUID and the time.
 * 
 * @see s3eNextpeerTournamentStartCallback
 */
typedef struct s3eNextpeerTournamentStartData {
	char m_tournamentUuid[S3E_NEXTPEER_STRING_MAX_1]; // Tournament UUID
	int m_tournamentSeconds; // Tournament time in seconds
} s3eNextpeerTournamentStartData;


// Function pointers
typedef void (*s3eNextpeerCBDidTournamentStartWithDetails)(s3eNextpeerTournamentStartData* ); // -(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
typedef void (*s3eNextpeerCBDidTournamentEnd)(); // -(void)nextpeerDidTournamentEnd

typedef struct s3eNextpeerDelegate {
	// Callback function for tournament start
	s3eNextpeerCBDidTournamentStartWithDetails m_DidTournamentStartCallback;
	
	// Callback function for tournament end
	s3eNextpeerCBDidTournamentEnd m_didTournamentEndCallback;
	
} s3eNextpeerDelegate;

typedef struct s3eNextpeerDelegatesContainer {
	// Nextpeer delegate
	s3eNextpeerDelegate m_NextpeerDelegate;
	
} s3eNextpeerDelegatesContainer;
// \cond HIDDEN_DEFINES
S3E_BEGIN_C_DECL
// \endcond

/**
 * Returns S3E_TRUE if the Nextpeer extension is available.
 */
s3eBool s3eNextpeerAvailable();

void s3eNextpeerInitWithProductKeyAndDelegatesContainer(const char* productKey, const s3eNextpeerDelegatesContainer* delegatesContainer);

void s3eNextpeerLaunchDashboard();

void s3eNextpeerShutDown();

S3E_END_C_DECL

#endif /* !S3E_EXT_NEXTPEER_H */
