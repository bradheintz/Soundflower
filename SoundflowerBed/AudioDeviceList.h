/*	Copyright: 	© Copyright 2004 Apple Computer, Inc. All rights reserved.

	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
			("Apple") in consideration of your agreement to the following terms, and your
			use, installation, modification or redistribution of this Apple software
			constitutes acceptance of these terms.  If you do not agree with these terms,
			please do not use, install, modify or redistribute this Apple software.

			In consideration of your agreement to abide by the following terms, and subject
			to these terms, Apple grants you a personal, non-exclusive license, under Apple’s
			copyrights in this original Apple software (the "Apple Software"), to use,
			reproduce, modify and redistribute the Apple Software, with or without
			modifications, in source and/or binary forms; provided that if you redistribute
			the Apple Software in its entirety and without modifications, you must retain
			this notice and the following text and disclaimers in all such redistributions of
			the Apple Software.  Neither the name, trademarks, service marks or logos of
			Apple Computer, Inc. may be used to endorse or promote products derived from the
			Apple Software without specific prior written permission from Apple.  Except as
			expressly stated in this notice, no other rights or licenses, express or implied,
			are granted by Apple herein, including but not limited to any patent rights that
			may be infringed by your derivative works or by other works in which the Apple
			Software may be incorporated.

			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
			WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
			WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
			PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
			COMBINATION WITH YOUR PRODUCTS.

			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
			CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
			GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
			ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
			OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
			(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
			ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*=============================================================================
	AudioDeviceList.h
	
=============================================================================*/

#ifndef __AudioDeviceList_h__
#define __AudioDeviceList_h__

#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudio.h>
#include <vector>
//#include <algorithm>    // std::sort
#include <map>

class AudioDeviceList {
public:
	struct Device {
		char			mName[64];
		AudioDeviceID	mID;
	};
	typedef std::vector<Device> DeviceList;

	AudioDeviceList(bool inputs);
	~AudioDeviceList();

	DeviceList &GetList() { return mDevices; }

    enum {kAudioDeviceTransportTypeHeadphones = 'hdpn' };
    typedef std::map<UInt32, UInt8> priorityMap;
    static priorityMap priorityTransportType;
    DeviceList &SortList(bool (*sortFunction)(Device&, Device&) = sortFun) { std::sort(mDevices.begin(), mDevices.end(), sortFunction); return mDevices; }

protected:
	void		BuildList();
	void		EraseList();

	bool		mInputs;
	DeviceList	mDevices;

    static priorityMap iniPriorityMap() {
        priorityMap m;

        m[kAudioDeviceTransportTypeHeadphones]      = 7;
        m[kAudioDeviceTransportTypeBluetooth]       = 6;
        m[kAudioDeviceTransportTypeBluetoothLE]     = 6;
        m[kAudioDeviceTransportTypeHDMI]            = 5;
        m[kAudioDeviceTransportTypeDisplayPort]     = 4;
        m[kAudioDeviceTransportTypeThunderbolt]     = 4;
        m[kAudioDeviceTransportTypeFireWire]        = 4;
        m[kAudioDeviceTransportTypeUSB]             = 4;
        m[kAudioDeviceTransportTypeBuiltIn]         = 3;
        m[kAudioDeviceTransportTypeAirPlay]         = 2;
        m[kAudioDeviceTransportTypePCI]             = 1;
        m[kAudioDeviceTransportTypeAggregate]       = 1;
        m[kAudioDeviceTransportTypeAutoAggregate]   = 1;
        m[kAudioDeviceTransportTypeAVB]             = 1;
        m[kAudioDeviceTransportTypeVirtual]         = 1;
        m[kAudioDeviceTransportTypeUnknown]         = 0;

        return m;
    }

    static bool sortFun(Device& x, Device& y);
	
};

#endif // __AudioDeviceList_h__
