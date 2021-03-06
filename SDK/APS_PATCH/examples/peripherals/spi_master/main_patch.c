/******************************************************************************
*  Copyright 2017 - 2018, Opulinks Technology Ltd.
*  ----------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/

/******************************************************************************
*  Filename:
*  ---------
*  main_patch.c
*
*  Project:
*  --------
*  OPL1000 Project - the main patch implement file
*
*  Description:
*  ------------
*  This implement file is include the main patch function and api.
*
*  Author:
*  -------
*  SH SDK
*
******************************************************************************/
/***********************
Head Block of The File
***********************/
// Sec 0: Comment block of the file
/******************************************************************************
*  Test code brief
*  These examples show how to configure spi settings and use spi driver APIs.
*
*  spi_flash_test() is an example of using SPI0 to access SPI flash. The operation is *   (1) write a block data to certain area. 
*   (2) then read it back and compare with original data.  
*   Flash area address begins from 0x00090000, size 1600 bytes. 
*       
*  spi_send_data() is an example of access an external SPI slave device through 
           SPI1 and SPI2 port 
*  
*  SPI1 and SPI2 signal pin and parameters are defined by OPL1000_periph.spi
* 
******************************************************************************/


// Sec 1: Include File
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "sys_init.h"
#include "sys_init_patch.h"
#include "hal_system.h"
#include "mw_fim.h"
#include "cmsis_os.h"
#include "sys_os_config.h"
#include "Hal_pinmux_spi.h"
#include "hal_flash_patch.h"
#include "hal_pin.h"
#include "hal_pin_def.h"
#include "hal_pin_config_project.h"

// Sec 2: Constant Definitions, Imported Symbols, miscellaneous
#define DUMMY          0x00
#define SPI1_IDX       0 
#define SPI2_IDX       0   // it is corresponding to the index in spi
#define TEST_SPI       SPI2_IDX

#define FLASH_START_ADDR  0x90   // 0x00090000
#define BLOCK_DATA_SIZE   1600   // bytes
#define SECTION_INDEX     0      // one section is 4 kbytes  
#define MIN_DATA_VALUE    50 
#define MAX_DATA_VALUE    200    // note:(MAX_DATA_VALUE + MIN_DATA_VALUE) < 255 

/********************************************
Declaration of data structure
********************************************/
// Sec 3: structure, union, enum, linked list


/********************************************
Declaration of Global Variables & Functions
********************************************/
// Sec 4: declaration of global variable


// Sec 5: declaration of global function prototype
typedef void (*T_Main_AppInit_fp)(void);
extern T_Main_AppInit_fp Main_AppInit;


/***************************************************
Declaration of static Global Variables & Functions
***************************************************/
// Sec 6: declaration of static global variable
static osThreadId g_tAppThread;

// Sec 7: declaration of static function prototype
static void __Patch_EntryPoint(void) __attribute__((section(".ARM.__at_0x00420000")));
static void __Patch_EntryPoint(void) __attribute__((used));
static void Main_PinMuxUpdate(void);
static void Main_FlashLayoutUpdate(void);
void Main_AppInit_patch(void);
static void spi_flash_test(void);
static void spi_send_data(int port);
static void Main_AppThread(void *argu);
static void spi_test(void);

/***********
C Functions
***********/
// Sec 8: C Functions

/*************************************************************************
* FUNCTION:
*   __Patch_EntryPoint
*
* DESCRIPTION:
*   the entry point of SW patch
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void __Patch_EntryPoint(void)
{
    // don't remove this code
    SysInit_EntryPoint();
    
    // update the pin mux
    Hal_SysPinMuxAppInit = Main_PinMuxUpdate;
    
    // update the flash layout
    MwFim_FlashLayoutUpdate = Main_FlashLayoutUpdate;
    
    // application init
    Sys_AppInit = Main_AppInit_patch;
}


/*************************************************************************
* FUNCTION:
*   Main_PinMuxUpdate
*
* DESCRIPTION:
*   update the pin-mux setting
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void Main_PinMuxUpdate(void)
{
    Hal_Pin_ConfigSet(0, HAL_PIN_TYPE_IO_0, HAL_PIN_DRIVING_IO_0);
    Hal_Pin_ConfigSet(1, HAL_PIN_TYPE_IO_1, HAL_PIN_DRIVING_IO_1);
    Hal_Pin_ConfigSet(2, HAL_PIN_TYPE_IO_2, HAL_PIN_DRIVING_IO_2);
    Hal_Pin_ConfigSet(3, HAL_PIN_TYPE_IO_3, HAL_PIN_DRIVING_IO_3);
    Hal_Pin_ConfigSet(4, HAL_PIN_TYPE_IO_4, HAL_PIN_DRIVING_IO_4);
    Hal_Pin_ConfigSet(5, HAL_PIN_TYPE_IO_5, HAL_PIN_DRIVING_IO_5);
    Hal_Pin_ConfigSet(6, HAL_PIN_TYPE_IO_6, HAL_PIN_DRIVING_IO_6);
    Hal_Pin_ConfigSet(7, HAL_PIN_TYPE_IO_7, HAL_PIN_DRIVING_IO_7);
    Hal_Pin_ConfigSet(8, HAL_PIN_TYPE_IO_8, HAL_PIN_DRIVING_IO_8);
    Hal_Pin_ConfigSet(9, HAL_PIN_TYPE_IO_9, HAL_PIN_DRIVING_IO_9);
    Hal_Pin_ConfigSet(10, HAL_PIN_TYPE_IO_10, HAL_PIN_DRIVING_IO_10);
    Hal_Pin_ConfigSet(11, HAL_PIN_TYPE_IO_11, HAL_PIN_DRIVING_IO_11);
    Hal_Pin_ConfigSet(12, HAL_PIN_TYPE_IO_12, HAL_PIN_DRIVING_IO_12);
    Hal_Pin_ConfigSet(13, HAL_PIN_TYPE_IO_13, HAL_PIN_DRIVING_IO_13);
    Hal_Pin_ConfigSet(14, HAL_PIN_TYPE_IO_14, HAL_PIN_DRIVING_IO_14);
    Hal_Pin_ConfigSet(15, HAL_PIN_TYPE_IO_15, HAL_PIN_DRIVING_IO_15);
    Hal_Pin_ConfigSet(16, HAL_PIN_TYPE_IO_16, HAL_PIN_DRIVING_IO_16);
    Hal_Pin_ConfigSet(17, HAL_PIN_TYPE_IO_17, HAL_PIN_DRIVING_IO_17);
    Hal_Pin_ConfigSet(18, HAL_PIN_TYPE_IO_18, HAL_PIN_DRIVING_IO_18);
    Hal_Pin_ConfigSet(19, HAL_PIN_TYPE_IO_19, HAL_PIN_DRIVING_IO_19);
    Hal_Pin_ConfigSet(20, HAL_PIN_TYPE_IO_20, HAL_PIN_DRIVING_IO_20);
    Hal_Pin_ConfigSet(21, HAL_PIN_TYPE_IO_21, HAL_PIN_DRIVING_IO_21);
    Hal_Pin_ConfigSet(22, HAL_PIN_TYPE_IO_22, HAL_PIN_DRIVING_IO_22);
    Hal_Pin_ConfigSet(23, HAL_PIN_TYPE_IO_23, HAL_PIN_DRIVING_IO_23);
}

/*************************************************************************
* FUNCTION:
*   Main_FlashLayoutUpdate
*
* DESCRIPTION:
*   update the flash layout
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void Main_FlashLayoutUpdate(void)
{
    // update here
}


/*************************************************************************
* FUNCTION:
*   App_Pin_InitConfig
*
* DESCRIPTION:
*   init the pin assignment. PinMux is determined by OPL1000_periph 
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
void App_Pin_InitConfig(void)
{
    printf("SPI initialization  \r\n");
    Hal_Pinmux_Spi_Init(&OPL1000_periph.spi[TEST_SPI]);    
}

/*************************************************************************
* FUNCTION:
*   Main_AppInit_patch
*
* DESCRIPTION:
*   the initial of application
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
void Main_AppInit_patch(void)
{
    // init the pin assignment
    App_Pin_InitConfig();	
	
		// flash write and read demo, use SPI0 to access on board SPI flash 
		spi_flash_test();				
		
	  // create a thread and run SPI access function 
    spi_test();

}

/*************************************************************************
* FUNCTION:
*   Main_AppThread
*
* DESCRIPTION:
*   the application thread 2
*
* PARAMETERS
*   1. argu     : [In] the input argument
*
* RETURNS
*   none
*
*************************************************************************/
static void Main_AppThread(void *argu)
{	
    while (1)
    {	
        osDelay(1500);      // delay 1500 ms		
        printf("SPI Running \r\n");			
				// communicate with external SPI slave device 
				spi_send_data(TEST_SPI); 			
    }
}

/*************************************************************************
* FUNCTION:
*   spi_flash_test
*
* DESCRIPTION:
*   an example that read and write data on SPI0 to access on board spi flash.
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void spi_flash_test(void)
{
 	
    uint8_t u8BlockData[BLOCK_DATA_SIZE],u8ReadData[BLOCK_DATA_SIZE] = {0};
    uint32_t i,u32Length,u32SectorAddr32bit;
    uint16_t u16SectorAddr;
    bool match_flag = true; 
    
    u32Length = BLOCK_DATA_SIZE;
      
    // prepare test block data 
    for (i=0; i<u32Length; i++)
        u8BlockData[i] = (i%MAX_DATA_VALUE) + MIN_DATA_VALUE;
      
    u16SectorAddr = FLASH_START_ADDR + SECTION_INDEX; // one section is 4k Bytes 

    u32SectorAddr32bit =  (((uint32_t)u16SectorAddr) << 12) & 0x000ff000;
    // Erase flash firstly  
    Hal_Flash_4KSectorAddrErase(SPI_IDX_0, u32SectorAddr32bit);
    // Write u8BlockData into flash   
    Hal_Flash_AddrProgram(SPI_IDX_0, u32SectorAddr32bit, 0, u32Length, u8BlockData);
    // Read flash content from SectorAddr32bit

    Hal_Flash_AddrRead(SPI_IDX_0, u32SectorAddr32bit, 0, u32Length, u8ReadData );
    for(i=0; i<u32Length; i++)
    {
        if(u8BlockData[i] != u8ReadData[i] )
        {
            printf("No.%d data error. write %x, read %x \r\n",i+1, u8BlockData[i],u8ReadData[i]);
            match_flag = false;
        }
    }

    if (match_flag == true)
    {
        printf("Write and read %d bytes data on flash @%x successfully \r\n",u32Length, u32SectorAddr32bit); 
    }	
		
}

/*************************************************************************
* FUNCTION:
*   spi_send_data
*
* DESCRIPTION:
*   an example of write data to external SPI slave device.
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void spi_send_data(int port)
{
    char output_str[32]= {0};   
    uint32_t u32Data, i, spi_idx = 0;
    T_OPL1000_Spi *spi;
		
    spi = &OPL1000_periph.spi[port];
		if (spi->index == SPI_IDX_1)
			  spi_idx = 1; // indicate it is SPI1 
	  else if (spi->index == SPI_IDX_2)
			  spi_idx = 2; // indicate it is SPI2 
		
    sprintf(output_str,"Hello from SPI%d \r\n",spi_idx);
    printf("Send data to external SPI%d slave device \r\n",spi_idx);    
    for(i=0;i<strlen(output_str);i++)
    {
        u32Data = output_str[i];
        Hal_Spi_Data_Send(spi->index,u32Data);
    }    
}

/*************************************************************************
* FUNCTION:
*   SPI test 
*
* DESCRIPTION:
*   This is a blank function, just create a thread 
*
* PARAMETERS
*   none
*
* RETURNS
*   none
*
*************************************************************************/
static void spi_test(void)
{
    osThreadDef_t tThreadDef;
    
    // create the thread for AppThread
    tThreadDef.name = "App";
    tThreadDef.pthread = Main_AppThread;
    tThreadDef.tpriority = OS_TASK_PRIORITY_APP;        // osPriorityNormal
    tThreadDef.instances = 0;                           // reserved, it is no used
    tThreadDef.stacksize = OS_TASK_STACK_SIZE_APP;      // (512), unit: 4-byte, the size is 512*4 bytes
    g_tAppThread = osThreadCreate(&tThreadDef, NULL);
    if (g_tAppThread == NULL)
    {
        printf("To create the thread for AppThread is fail.\n");
    }	
}

