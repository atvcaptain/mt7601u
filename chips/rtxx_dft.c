/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	rtxx_dft.c

	Abstract:
	Ralink Wireless driver chip default init functions

	Revision History:
	Who         When          What
	--------    ----------    ----------------------------------------------
*/
#include "rt_config.h"



FREQUENCY_ITEM RtmpFreqItems3020[] =
{	
	/* ISM : 2.4 to 2.483 GHz,  11g */
	/*-CH---N-------R---K-----------*/
	{1,    241,  2,  2},
	{2,    241,	 2,  7},
	{3,    242,	 2,  2},
	{4,    242,	 2,  7},
	{5,    243,	 2,  2},
	{6,    243,	 2,  7},
	{7,    244,	 2,  2},
	{8,    244,	 2,  7},
	{9,    245,	 2,  2},
	{10,   245,	 2,  7},
	{11,   246,	 2,  2},
	{12,   246,	 2,  7},
	{13,   247,	 2,  2},
	{14,   248,	 2,  4},
};

FREQUENCY_ITEM FreqItems3020_Xtal20M[] =
{	
	/*
	 * RF_R08:
	 * <7:0>: pll_N<7:0>
	 *
	 * RF_R09:
	 * <3:0>: pll_K<3:0>
	 * <4>: pll_N<8>
	 * <7:5>pll_N<11:9>
	 *
	 */
	/*-CH---N--------R---N[7:4]K[3:0]------*/
	{1,    0xE2,     2,  0x14},
	{2,    0xE3,	 2,  0x14},
	{3,    0xE4,	 2,  0x14},
	{4,    0xE5,	 2,  0x14},
	{5,    0xE6,	 2,  0x14},
	{6,    0xE7,	 2,  0x14},
	{7,    0xE8,	 2,  0x14},
	{8,    0xE9,	 2,  0x14},
	{9,    0xEA,	 2,  0x14},
	{10,   0xEB,	 2,  0x14},
	{11,   0xEC,	 2,  0x14},
	{12,   0xED,	 2,  0x14},
	{13,   0xEE,	 2,  0x14},
	{14,   0xF0,	 2,  0x18},
};

UCHAR	NUM_OF_3020_CHNL = (sizeof(RtmpFreqItems3020) / sizeof(FREQUENCY_ITEM));

FREQUENCY_ITEM *FreqItems3020 = RtmpFreqItems3020;


#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 

/* The Tx power tuning entry*/
const TX_POWER_TUNING_ENTRY_STRUCT TxPowerTuningTableOrg[] = 
{
/*	idxTxPowerTable		Tx power control over RF			Tx power control over MAC*/
/*	(zero-based array)		{ RF R12[4:0]: Tx0 ALC},			{MAC 0x1314~0x1324}*/
/*	0	*/				{0x00, 							-15}, 
/*	1	*/				{0x01, 							-15}, 
/*	2	*/				{0x00, 							-14}, 
/*	3	*/				{0x01, 							-14}, 
/*	4	*/				{0x00, 							-13}, 
/*	5	*/				{0x01, 							-13}, 
/*	6	*/				{0x00, 							-12}, 
/*	7	*/				{0x01, 							-12}, 
/*	8	*/				{0x00, 							-11}, 
/*	9	*/				{0x01, 							-11}, 
/*	10	*/				{0x00, 							-10}, 
/*	11	*/				{0x01, 							-10}, 
/*	12	*/				{0x00, 							-9}, 
/*	13	*/				{0x01, 							-9}, 
/*	14	*/				{0x00, 							-8}, 
/*	15	*/				{0x01, 							-8}, 
/*	16	*/				{0x00, 							-7}, 
/*	17	*/				{0x01, 							-7}, 
/*	18	*/				{0x00, 							-6}, 
/*	19	*/				{0x01, 							-6}, 
/*	20	*/				{0x00, 							-5}, 
/*	21	*/				{0x01, 							-5}, 
/*	22	*/				{0x00, 							-4}, 
/*	23	*/				{0x01, 							-4}, 
/*	24	*/				{0x00, 							-3}, 
/*	25	*/				{0x01, 							-3}, 
/*	26	*/				{0x00,							-2}, 
/*	27	*/				{0x01, 							-2}, 
/*	28	*/				{0x00, 							-1}, 
/*	29	*/				{0x01, 							-1}, 
/*	30	*/				{0x00,							0}, 
/*	31	*/				{0x01,							0}, 
/*	32	*/				{0x02,							0}, 
/*	33	*/				{0x03,							0}, 
/*	34	*/				{0x04,							0}, 
/*	35	*/				{0x05,							0}, 
/*	36	*/				{0x06,							0}, 
/*	37	*/				{0x07,							0}, 
/*	38	*/				{0x08,							0}, 
/*	39	*/				{0x09,							0}, 
/*	40	*/				{0x0A,							0}, 
/*	41	*/				{0x0B,							0}, 
/*	42	*/				{0x0C,							0}, 
/*	43	*/				{0x0D,							0}, 
/*	44	*/				{0x0E,							0}, 
/*	45	*/				{0x0F,							0}, 
/*	46	*/				{0x0F-1,							1}, 
/*	47	*/				{0x0F,							1}, 
/*	48	*/				{0x0F-1,							2}, 
/*	49	*/				{0x0F,							2}, 
/*	50	*/				{0x0F-1,							3}, 
/*	51	*/				{0x0F,							3}, 
/*	52	*/				{0x0F-1,							4}, 
/*	53	*/				{0x0F,							4}, 
/*	54	*/				{0x0F-1,							5}, 
/*	55	*/				{0x0F,							5}, 
/*	56	*/				{0x0F-1,							6}, 
/*	57	*/				{0x0F,							6}, 
/*	58	*/				{0x0F-1,							7}, 
/*	59	*/				{0x0F,							7}, 
/*	60	*/				{0x0F-1,							8}, 
/*	61	*/				{0x0F,							8}, 
/*	62	*/				{0x0F-1,							9}, 
/*	63	*/				{0x0F,							9}, 
/*	64	*/				{0x0F-1,							10}, 
/*	65	*/				{0x0F,							10}, 
/*	66	*/				{0x0F-1,							11}, 
/*	67	*/				{0x0F,							11}, 
/*	68	*/				{0x0F-1,							12}, 
/*	69	*/				{0x0F,							12}, 
/*	70	*/				{0x0F-1,							13}, 
/*	71	*/				{0x0F,							13}, 
/*	72	*/				{0x0F-1,							14}, 
/*	73	*/				{0x0F,							14}, 
/*	74	*/				{0x0F-1,							15}, 
/*	75	*/				{0x0F,							15}, 
};
#endif /* RTMP_INTERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */


#ifdef IQ_CAL_SUPPORT
VOID IQCalibrationViaBBPAccessSpace(
	IN PRTMP_ADAPTER 	pAd,
	IN UCHAR 			Channel)
{
	INT 		BBPIndex;
	UINT16 	E2PValue;

#ifdef RELEASE_EXCLUDE
	/* 
	    This function is an old way to do IQ compensation and restricted for RT5370/90/50 use only.
	    A new way is by EEPROM 0x130~0x142, which reserved as dedicated space for IQ mismatch information.
	*/
#endif /* RELEASE_EXCLUDE */

	/* IQ Calibration */
	if (Channel <= 14)
	{
		for (BBPIndex = 0; BBPIndex <= 7; BBPIndex++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_IQ_GLOBAL_BBP_ACCESS_BASE + (BBPIndex * 2), E2PValue);
			
			if (E2PValue == 0xFFFF)
			{
				DBGPRINT(RT_DEBUG_INFO, ("%s() : EEPROM 0x%X is not calibrated !\n", __FUNCTION__, 
					(EEPROM_IQ_GLOBAL_BBP_ACCESS_BASE + (BBPIndex * 2))));
				continue;
			}
			else
			{
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, (UCHAR)((E2PValue >> 8) & 0x00FF), (UCHAR)(E2PValue & 0x00FF));
			}
		}
	}
	else
		DBGPRINT(RT_DEBUG_ERROR, ("%s() : 5 GHz band not supported !\n", __FUNCTION__));
}
#endif /* IQ_CAL_SUPPORT */


static VOID RxSensitivityTuning(RTMP_ADAPTER *pAd)
{
	UCHAR R66 = 0x26 + pAd->hw_cfg.lan_gain;

#ifdef CONFIG_ATE
	if (ATE_ON(pAd))
	{
#ifdef RT2883
		if (IS_RT2883(pAd))
		{
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R27, 0x0);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R27, 0x20);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R27, 0x40);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		}
		else
#endif /* RT2883*/
#ifdef RT3352
		if (IS_RT3352(pAd))
		{
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R27, 0x0);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R27, 0x20);
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		}
		else
#endif /* RT3352 */
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
	}
	else
#endif /* CONFIG_ATE */
	{
		bbp_set_agc(pAd, R66, RX_CHAIN_ALL);
	}
	DBGPRINT(RT_DEBUG_TRACE,("turn off R17 tuning, restore to 0x%02x\n", R66));
}


#ifdef CONFIG_STA_SUPPORT
static UCHAR ChipAGCAdjust(
	IN PRTMP_ADAPTER		pAd,
	IN CHAR					Rssi,
	IN UCHAR				OrigR66Value)
{
	UCHAR R66 = OrigR66Value;
	CHAR lanGain = pAd->hw_cfg.lan_gain;
	
	if (pAd->LatchRfRegs.Channel <= 14)
	{	/*BG band*/
		R66 = 0x2E + lanGain;
		if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
			R66 += 0x10;
	}
	else
	{	/*A band*/
		if (pAd->CommonCfg.BBPCurrentBW == BW_20)
			R66 = 0x32 + (lanGain * 5) / 3;
		else
			R66 = 0x3A + (lanGain * 5) / 3;

		if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
				R66 += 0x10;
	}

	if (OrigR66Value != R66)
		bbp_set_agc(pAd, R66, RX_CHAIN_ALL);

#ifdef RT30xx
	if (IS_RT3390(pAd))
	{
		UCHAR BbpData = 0;

		/* Reduce the RX I/Q target level to improve maximum high power input*/
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R67, &BbpData);
		if (pAd->StaCfg.RssiSample.AvgRssi[0] > -30)
			BbpData = ((BbpData & 0x80) | 0x18); /* The desired signal level after AGC*/
		else
			BbpData = ((BbpData & 0x80) | 0x20); /* The desired signal level after AGC*/
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R67, BbpData);
	}
#endif /* RT30xx */

	return R66;
}
#endif /* CONFIG_STA_SUPPORT */


static VOID ChipBBPAdjust(RTMP_ADAPTER *pAd)
{
	UCHAR bbp_val;
	UINT8 rf_bw, ext_ch;

#ifdef DOT11_N_SUPPORT
	if (get_ht_cent_ch(pAd, &rf_bw, &ext_ch) == FALSE)
#endif /* DOT11_N_SUPPORT */
	{
		rf_bw = BW_20;
		ext_ch = EXTCHA_NONE;
		pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel;
	}

	bbp_set_bw(pAd, rf_bw);

	/*  TX/RX : control channel setting */
	rtmp_mac_set_ctrlch(pAd, ext_ch);
	bbp_set_ctrlch(pAd, ext_ch);

	/* request by Gary 20070208 for middle and long range G Band*/
#ifdef DOT11_N_SUPPORT
	if (rf_bw == BW_40)
		bbp_val = (pAd->CommonCfg.Channel > 14) ? 0x48 : 0x38;
	else
#endif /* DOT11_N_SUPPORT */
		bbp_val = (pAd->CommonCfg.Channel > 14) ? 0x40 : 0x38;
	bbp_set_agc(pAd, bbp_val, RX_CHAIN_ALL);


	if (pAd->MACVersion == 0x28600100)
	{
#ifdef RT28xx
		RT28xx_ch_tunning(pAd, BW_40);
#endif /* RT28xx */
	}
	else
	{
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R69, 0x12);
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, 0x0A);
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, 0x10);
	}

	DBGPRINT(RT_DEBUG_TRACE, ("%s(): BW_%s, ChannelWidth=%d, Channel=%d, ExtChanOffset=%d(%d) \n",
					__FUNCTION__, (rf_bw == BW_40 ? "40" : "20"),
					pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth, 
					pAd->CommonCfg.Channel, 
					pAd->CommonCfg.RegTransmitSetting.field.EXTCHA,
					pAd->CommonCfg.AddHTInfo.AddHtInfo.ExtChanOffset));

	/* request by Gary 20070208 for middle and long range A Band*/
	if (pAd->CommonCfg.Channel > 14)
		bbp_val = 0x1D;
	else
		bbp_val = 0x2D;
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, bbp_val);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, bbp_val);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, bbp_val);
	/*RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, bbp_val);*/
}


static VOID Default_ChipSwitchChannel(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR Channel,
	IN BOOLEAN bScan) 
{
	DBGPRINT(RT_DEBUG_ERROR, ("%s(): dummy channel switch function!\n", __FUNCTION__));

	pAd->LatchRfRegs.Channel = Channel;
	pAd->hw_cfg.lan_gain = GET_LNA_GAIN(pAd);
}


static VOID Default_ChipAGCInit(RTMP_ADAPTER *pAd, UCHAR BandWidth)
{
	UCHAR R66 = 0x30, lan_gain;


	lan_gain = pAd->hw_cfg.lan_gain;
	if (pAd->LatchRfRegs.Channel <= 14)
	{	// BG band
#ifdef RT30xx
		/* Gary was verified Amazon AP and find that RT307x has BBP_R66 invalid default value */
		if (IS_RT3070(pAd)||IS_RT3090(pAd) || IS_RT3572(pAd) || IS_RT3390(pAd) || IS_RT3593(pAd))
			R66 = 0x1C + 2 * lan_gain;
		else
#endif // RT30xx //
		{
			R66 = 0x2E + lan_gain;
#if defined(RT3352)
			if (IS_RT3352(pAd))
			{
				/* Gary 20100714: Update BBP R66 programming: */
				if (pAd->CommonCfg.BBPCurrentBW == BW_20)
					R66 = (lan_gain * 2 + 0x1C);
				else
					R66 = (lan_gain * 2 + 0x24);
			}
#endif // defined(RT3352) //
		}
	}
	else
	{	//A band
#ifdef RT35xx
		if (IS_RT3572(pAd) || IS_RT3593(pAd))
			R66 = (UCHAR)(0x22 + (lan_gain * 5) / 3);
		else
#endif // RT35xx //
		{	
			if (BandWidth == BW_20)
				R66 = (UCHAR)(0x32 + (lan_gain * 5) / 3);
#ifdef DOT11_N_SUPPORT
			else
				R66 = (UCHAR)(0x3A + (lan_gain * 5) / 3);
#endif // DOT11_N_SUPPORT //
		}
	}
	bbp_set_agc(pAd, R66, RX_CHAIN_ALL);

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s():Ch=%d, BandWidth=%d, LNA_GAIN=0x%x, set R66 as 0x%x \n",
			__FUNCTION__, pAd->LatchRfRegs.Channel, BandWidth, lan_gain, R66));
#endif // RELEASE_EXCLUDE //
}


static VOID AsicAntennaDefaultReset(
	IN PRTMP_ADAPTER		pAd,
	IN EEPROM_ANTENNA_STRUC	*pAntenna)
{
#ifdef RT30xx
	if(IS_RT3090(pAd))
	{
		pAntenna->word = 0;
		pAntenna->field.RfIcType = RFIC_3020;
		pAntenna->field.TxPath = 1;
		pAntenna->field.RxPath = 1;		
	}
	else
#endif /* RT30xx */
#ifdef RT35xx
	if(IS_RT3572(pAd))
	{
		pAntenna->word = 0;
		pAntenna->field.RfIcType = RFIC_3052;
		pAntenna->field.TxPath = 2;
		pAntenna->field.RxPath = 2;		
	}
	else
#endif /* RT35xx */
#ifdef RT33xx
	if (IS_RT3390(pAd))
	{
		pAntenna->word = 0;
		pAntenna->field.RfIcType = RFIC_3320;
		pAntenna->field.TxPath = 1;
		pAntenna->field.RxPath = 1;
	}
	else
#endif /* RT33xx */
#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392)
	if (IS_RT5390(pAd) || IS_RT5392(pAd))
	{
		pAntenna->word = 0;
		pAntenna->field.RfIcType = 0xF; /* Reserved */
		pAntenna->field.BoardType = 1;
		if (IS_RT5392(pAd))
		{
			pAntenna->field.TxPath = 2;
			pAntenna->field.RxPath = 2;
		}
		else
		{
			pAntenna->field.TxPath = 1;
			pAntenna->field.RxPath = 1;
		}
	}
	else
#endif /* defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) */
#if defined(RT2883) || defined(RT3593)
	if (IS_RT2883(pAd))
	{
		pAntenna->word = 0;
#ifdef RT2883
	if (IS_RT2883(pAd))
		pAntenna->field.RfIcType = RFIC_2853;
#endif /* RT2883 */
#ifdef RT3593
	if (IS_RT3593(pAd))
		pAntenna->field.RfIcType = RFIC_3053;
#endif /* RT3593 */
		pAntenna->field.TxPath = 3;
		pAntenna->field.RxPath = 3;
	}
	else
#endif /* defined(RT2883) || defined(RT3593) */
#ifdef RT5350
	if (IS_RT5350(pAd))
	{
		pAntenna->word = 0;
		pAntenna->field.RfIcType = RFIC_3320;
		pAntenna->field.TxPath = 1;
		pAntenna->field.RxPath = 1;
	}
	else
#endif /* RT5350 */
	{

		pAntenna->word = 0;
		pAntenna->field.RfIcType = RFIC_2820;
		pAntenna->field.TxPath = 1;
		pAntenna->field.RxPath = 2;
	}
	DBGPRINT(RT_DEBUG_WARN, ("E2PROM error, hard code as 0x%04x\n", pAntenna->word));	
}


VOID NetDevNickNameInit(
	IN PRTMP_ADAPTER		pAd)
{
#ifdef CONFIG_STA_SUPPORT
#ifdef RTMP_MAC_PCI
#ifdef RT35xx
	if (IS_RT3572(pAd))
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT3562STA");
	else
#endif /* RT35xx*/
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT2860STA");
#endif /* RTMP_MAC_PCI */
#ifdef RTMP_MAC_USB
#ifdef RT35xx
	if (IS_RT3572(pAd))
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT3572STA");
	else if (IS_RT3070(pAd) && !IS_RT2070(pAd))
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT3070STA");
	else if (IS_RT3071(pAd) && !IS_RT2070(pAd))
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT3071STA");
	else if (IS_RT2070(pAd))
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT2070STA");
	else
#endif /* RT35xx*/
		snprintf((RTMP_STRING *) pAd->nickname, sizeof(pAd->nickname), "RT2870STA");
#endif /* RTMP_MAC_USB */
#endif /* CONFIG_STA_SUPPORT */
}


VOID RTxx_default_Init(RTMP_ADAPTER *pAd)
{
	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;


	/* init default value whatever chipsets */
	/* default pChipOps content will be 0x00 */
	pChipCap->bbpRegTbSize = 0;
	pChipCap->MaxNumOfRfId = 31;
	pChipCap->MaxNumOfBbpId = 136;
	pChipCap->SnrFormula = SNR_FORMULA1;
	pChipCap->RfReg17WtMethod = RF_REG_WT_METHOD_NONE;
	pChipCap->TXWISize = 16;
	pChipCap->RXWISize = 16;
#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION)
	pChipCap->TxPowerTuningTable_2G = TxPowerTuningTableOrg;
#ifdef A_BAND_SUPPORT
	pChipCap->TxPowerTuningTable_5G = TxPowerTuningTableOrg;
#endif /* A_BAND_SUPPORT */
#endif /* defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) */
	pChipOps->AsicMacInit = NULL;
	pChipOps->AsicBbpInit = NULL;
	pChipOps->AsicRfInit = NULL;

#ifdef RTMP_EFUSE_SUPPORT
	pChipCap->EFUSE_USAGE_MAP_START = 0x2d0;
	pChipCap->EFUSE_USAGE_MAP_END = 0x2fc;      
#ifdef RT5390
	if (IS_RT5390R(pAd))
		pChipCap->EFUSE_USAGE_MAP_SIZE = 29;
	else
#endif /* RT5390 */
       	pChipCap->EFUSE_USAGE_MAP_SIZE = 45;
	pChipCap->EFUSE_RESERVED_SIZE = pChipCap->EFUSE_USAGE_MAP_SIZE - 5;
#endif /* RTMP_EFUSE_SUPPORT */

	pChipCap->VcoPeriod = 10;
	pChipCap->FlgIsVcoReCalMode = VCO_CAL_DISABLE;
	pChipCap->WPDMABurstSIZE = 2; /* default 64B */
	pChipCap->MBSSIDMode = MBSSID_MODE0; 

#ifdef DOT11W_PMF_SUPPORT
        pChipCap->FlgPMFEncrtptMode = PMF_ENCRYPT_MODE_0;
#endif /* DOT11W_PMF_SUPPORT */

	RtmpChipBcnInit(pAd);

	pChipOps->RxSensitivityTuning = RxSensitivityTuning;
#ifdef CONFIG_STA_SUPPORT
	pChipOps->ChipAGCAdjust = ChipAGCAdjust;
#endif /* CONFIG_STA_SUPPORT */
	pChipOps->ChipBBPAdjust = ChipBBPAdjust;
	pChipOps->ChipSwitchChannel = Default_ChipSwitchChannel;

	/* TX ALC */
	pChipCap->bTempCompTxALC = FALSE;
	pChipOps->AsicGetTxPowerOffset = NULL;
	pChipOps->InitDesiredTSSITable = NULL;
	pChipOps->AsicTxAlcGetAutoAgcOffset = NULL;
	pChipOps->AsicExtraPowerOverMAC = NULL;
	pChipOps->AsicAdjustTxPower = AsicAdjustTxPower;

	pChipOps->ChipAGCInit = Default_ChipAGCInit;
	pChipOps->AsicAntennaDefaultReset = AsicAntennaDefaultReset;
	pChipOps->NetDevNickNameInit = NetDevNickNameInit;
	/* Init value. If pChipOps->AsicResetBbpAgent==NULL, "AsicResetBbpAgent" as default. If your chipset has specific routine, please re-hook it at self init function */
	pChipOps->AsicResetBbpAgent = NULL;

	pChipOps->InitTemperCompensation = NULL;
	pChipOps->TemperCompensation = NULL;

#ifdef RT28xx
	RT28xx_chip_Init(pAd);
#endif /* RT28xx */
#ifdef CARRIER_DETECTION_SUPPORT
	pChipCap->carrier_func = DISABLE_TONE_RADAR;
	pChipOps->ToneRadarProgram = NULL;
#endif /* CARRIER_DETECTOIN_SUPPORT */
#ifdef DFS_SUPPORT
	pChipCap->DfsEngineNum = 4;
#endif /* DFS_SUPPORT */
	pChipOps->CckMrcStatusCtrl = NULL;
	pChipOps->RadarGLRTCompensate = NULL;
#if 0
#ifdef DYNAMIC_VGA_SUPPORT
	pChipOps->AsicDynamicVgaGainControl = NULL;
#endif /* DYNAMIC_VGA_SUPPORT */
#endif
}

