/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 6 sept. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018 Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * 
 * Add a such file in the main Src directory for executing
 * you own workload.
 *
 * ==========================================================
 */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/time/time.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>
#include <it_sdk/statemachine/statemachine.h>
#include <it_sdk/eeprom/eeprom.h>

#include <it_sdk/lorawan/lorawan.h>
#include <it_sdk/encrypt/encrypt.h>
#include <it_sdk/eeprom/securestore.h>
#include <it_sdk/lowpower/lowpower.h>


#define LED1_PORT __BANK_B
#define LED1_PIN __LP_GPIO_5
#define LED2_PORT __BANK_A
#define LED2_PIN __LP_GPIO_5
#define LED3_PORT __BANK_B
#define LED3_PIN __LP_GPIO_6
#define LED4_PORT __BANK_B
#define LED4_PIN __LP_GPIO_7
#define BUTTON_PORT	__BANK_B
#define BUTTON_PIN __LP_GPIO_2

// =====================================================================
// Manage the device configuration (eeprom)

#define VERSION 0x01
struct conf {
		uint8_t			version;
} s_conf;

void loadConfig() {

	uint8_t v;
	if ( ! eeprom_read(&s_conf, sizeof(s_conf), VERSION,&v) ) {
		log_info("Flash the initial configuration\r\n");
		s_conf.version = VERSION;
		eeprom_write(&s_conf, sizeof(s_conf), VERSION);
	} else {
		log_info("Loaded version %d\r\n",v);
	}
}

// =====================================================================
// Manage the device state (ram)

struct state {
	uint8_t 	led;
	uint32_t  	loops;
} s_state;

void initState() {
	s_state.led = GPIO_PIN_SET;
	s_state.loops = 0;
}

// =====================================================================
// Setup
void task();

void project_setup() {
	log_init(ITSDK_LOGGER_CONF);
	log_info("Booting \r\n");
	// reboot cause
	log_info("Reset : %d\r\n",itsdk_getResetCause());
	//itsdk_cleanResetCause();

	// Init at boot time
	loadConfig();
	initState();
	gpio_reset(LED1_PORT, LED1_PIN);
	gpio_reset(LED3_PORT, LED3_PIN);
	gpio_reset(LED4_PORT, LED4_PIN);

	uint8_t consolePass[16];
	itsdk_secstore_readBlock(ITSDK_SS_CONSOLEKEY, consolePass);


	// Init LoRaWan stack
	static itsdk_lorawan_channelInit_t channels= ITSDK_LORAWAN_CHANNEL;
	#ifdef ITSDK_LORAWAN_CHANNEL
		itsdk_lorawan_setup(__LORAWAN_REGION_EU868,&channels);
	#else
		itsdk_lorawan_setup(__LORAWAN_REGION_EU868,NULL);
	#endif

	itdt_sched_registerSched(30000,ITSDK_SCHED_CONF_IMMEDIATE, &task);
}

// =====================================================================
// What to do

void send_callback(itsdk_lorawan_send_t status, uint8_t port, uint8_t size, uint8_t * rxData) {
	gpio_reset(LED2_PORT,LED2_PIN);
	switch ( status ) {
	case LORAWAN_SEND_ACKED_WITH_DOWNLINK:
		// case with downlink data
	case LORAWAN_SEND_ACKED_WITH_DOWNLINK_PENDING:
		// case with downlink data + pending downlink on server side.
	case LORAWAN_SEND_ACKED:
		gpio_set(LED3_PORT,LED3_PIN);
		break;
	case LORAWAN_SEND_SENT:
		gpio_set(LED4_PORT,LED4_PIN);
		break;
	default:
		break;
	}
}

void task() {
	uint8_t t[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

	if ( !itsdk_lorawan_hasjoined() ) {
		if ( itsdk_lorawan_join_sync() == LORAWAN_JOIN_SUCCESS ) {
			gpio_set(LED1_PORT,LED1_PIN);
		} else {
			gpio_reset(LED1_PORT,LED1_PIN);
		}
	} else {
		gpio_set(LED2_PORT,LED2_PIN);
		gpio_reset(LED3_PORT,LED3_PIN);
		gpio_reset(LED4_PORT,LED4_PIN);
		itsdk_lorawan_send_t r = itsdk_lorawan_send_async(
				t,
				16,
				1,
				__LORAWAN_DR_5,
				LORAWAN_SEND_CONFIRMED,
				ITSDK_LORAWAN_CNF_RETRY,
				send_callback,
				/*PAYLOAD_ENCRYPT_AESCTR | PAYLOAD_ENCRYPT_SPECK |*/ PAYLOAD_ENCRYPT_NONE
		);
		if ( r != LORAWAN_SEND_RUNNING ) {
			log_warn("an error has bene reported : %d\r\n",r);
		}
	}
	log_info("time is %d\r\n",(uint32_t)itsdk_time_get_ms());

}


/**
 * Project loop may not contain functional stuff
 * Keep in this loop only really short operations
 */
void project_loop() {
	itsdk_lorawan_loop();
	if( gpio_read(BUTTON_PORT, BUTTON_PIN) == 0 ) {
		lowPower_disable();
		log_info("LowPowerOff\r\n");
		itsdk_delayMs(200);
	}

}

