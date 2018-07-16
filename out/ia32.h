/** @file */
#pragma once
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

/**
 * @defgroup INTEL_MANUAL \
 *           Intel Manual
 *
 * @remarks All references are based on <b>Intel(R) 64 and IA-32 architectures software developer's manual combined volumes:
 *          1, 2A, 2B, 2C, 2D, 3A, 3B, 3C, 3D, and 4</b> (May 2018).
 * @{
 */
/**
 * @defgroup CONTROL_REGISTERS \
 *           Control registers
 *
 * Control registers (CR0, CR1, CR2, CR3, and CR4) determine operating mode of the processor and the characteristics of the
 * currently executing task. These registers are 32 bits in all 32-bit modes and compatibility mode.
 * In 64-bit mode, control registers are expanded to 64 bits. The MOV CRn instructions are used to manipulate the register
 * bits. Operand-size prefixes for these instructions are ignored. The following is also true:
 * - The control registers can be read and loaded (or modified) using the move-to-or-from-control-registers forms of the
 * MOV instruction. In protected mode, the MOV instructions allow the control registers to be read or loaded (at privilege
 * level 0 only). This restriction means that application programs or operating-system procedures (running at privilege
 * levels 1, 2, or 3) are prevented from reading or loading the control registers.
 * - Bits 63:32 of CR0 and CR4 are reserved and must be written with zeros. Writing a nonzero value to any of the upper 32
 * bits results in a general-protection exception, \#GP(0).
 * - All 64 bits of CR2 are writable by software.
 * - Bits 51:40 of CR3 are reserved and must be 0.
 * - The MOV CRn instructions do not check that addresses written to CR2 and CR3 are within the linear-address or
 * physical-address limitations of the implementation.
 * - Register CR8 is available in 64-bit mode only. The control registers are summarized below, and each architecturally
 * defined control field in these control registers is described individually.
 * - CR0 - Contains system control flags that control operating mode and states of the processor.
 * - CR1 - Reserved.
 * - CR2 - Contains the page-fault linear address (the linear address that caused a page fault).
 * - CR3 - Contains the physical address of the base of the paging-structure hierarchy and two flags (PCD and PWT). Only
 * the most-significant bits (less the lower 12 bits) of the base address are specified; the lower 12 bits of the address
 * are assumed to be 0. The first paging structure must thus be aligned to a page (4-KByte) boundary. The PCD and PWT flags
 * control caching of that paging structure in the processor's internal data caches (they do not control TLB caching of
 * page-directory information). When using the physical address extension, the CR3 register contains the base address of
 * the page-directorypointer table. In IA-32e mode, the CR3 register contains the base address of the PML4 table.
 * - CR4 - Contains a group of flags that enable several architectural extensions, and indicate operating system or
 * executive support for specific processor capabilities.
 * - CR8 - Provides read and write access to the Task Priority Register (TPR). It specifies the priority threshold value
 * that operating systems use to control the priority class of external interrupts allowed to interrupt the processor. This
 * register is available only in 64-bit mode. However, interrupt filtering continues to apply in compatibility mode.
 *
 * @see Vol3A[2.5(CONTROL REGISTERS)] (reference)
 * @{
 */
typedef union
{
  struct
  {
    UINT64 ProtectionEnable                                        : 1;
    UINT64 MonitorCoprocessor                                      : 1;
    UINT64 EmulateFpu                                              : 1;
    UINT64 TaskSwitched                                            : 1;
    UINT64 ExtensionType                                           : 1;
    UINT64 NumericError                                            : 1;
    UINT64 Reserved1                                               : 10;
    UINT64 WriteProtect                                            : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 AlignmentMask                                           : 1;
    UINT64 Reserved3                                               : 10;
    UINT64 NotWriteThrough                                         : 1;
    UINT64 CacheDisable                                            : 1;
    UINT64 PagingEnable                                            : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR0;

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 3;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Reserved2                                               : 7;
    UINT64 AddressOfPageDirectory                                  : 36;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR3;

typedef union
{
  struct
  {
    UINT64 VirtualModeExtensions                                   : 1;
    UINT64 ProtectedModeVirtualInterrupts                          : 1;
    UINT64 TimestampDisable                                        : 1;
    UINT64 DebuggingExtensions                                     : 1;
    UINT64 PageSizeExtensions                                      : 1;
    UINT64 PhysicalAddressExtension                                : 1;
    UINT64 MachineCheckEnable                                      : 1;
    UINT64 PageGlobalEnable                                        : 1;
    UINT64 PerformanceMonitoringCounterEnable                      : 1;
    UINT64 OsFxsaveFxrstorSupport                                  : 1;
    UINT64 OsXmmExceptionSupport                                   : 1;
    UINT64 UsermodeInstructionPrevention                           : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 VmxEnable                                               : 1;
    UINT64 SmxEnable                                               : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 FsgsbaseEnable                                          : 1;
    UINT64 PcidEnable                                              : 1;
    UINT64 OsXsave                                                 : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 SmepEnable                                              : 1;
    UINT64 SmapEnable                                              : 1;
    UINT64 ProtectionKeyEnable                                     : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR4;

typedef union
{
  struct
  {
    UINT64 TaskPriorityLevel                                       : 4;
    UINT64 Reserved                                                : 60;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} CR8;

/**
 * @}
 */

/**
 * @defgroup CPUID \
 *           CPUID
 *
 * @see Vol2A[3.2(CPUID)] (reference)
 * @{
 */
/**
 * @brief Returns CPUID's Highest Value for Basic Processor Information and the Vendor Identification String
 *
 * When CPUID executes with EAX set to 0, the processor returns the highest value the CPUID recognizes for returning basic
 * processor information. The value is returned in the EAX register and is processor specific.
 * A vendor identification string is also returned in EBX, EDX, and ECX. For Intel processors, the string is "GenuineIntel"
 * and is expressed:
 * - EBX <- 756e6547h (* "Genu", with G in the low eight bits of BL *)
 * - EDX <- 49656e69h (* "ineI", with i in the low eight bits of DL *)
 * - ECX <- 6c65746eh (* "ntel", with n in the low eight bits of CL *)
 */
typedef struct
{
  UINT32 MaxCpuidInputValue;
  UINT32 EbxValueGenu;
  UINT32 EcxValueNtel;
  UINT32 EdxValueInei;
} CPUID_EAX_00;

/**
 * @brief Returns Model, Family, Stepping Information, Additional Information and Feature Information
 *
 * Returns:
 *   * Model, Family, Stepping Information in EAX
 *   * Additional Information in EBX
 *   * Feature Information in ECX and EDX
 */
typedef struct
{
  /**
   * @brief When CPUID executes with EAX set to 01H, version information is returned in EAX
   */
  union
  {
    struct
    {
      UINT32 SteppingId                                            : 4;
      UINT32 Model                                                 : 4;
      UINT32 FamilyId                                              : 4;
      UINT32 ProcessorType                                         : 2;
      UINT32 Reserved1                                             : 2;
      UINT32 ExtendedModelId                                       : 4;
      UINT32 ExtendedFamilyId                                      : 8;
    };

    UINT32 Flags;
  } CpuidVersionInformation;

  /**
   * @brief When CPUID executes with EAX set to 01H, additional information is returned to the EBX register
   */
  struct
  {
    UINT8 BrandIndex;
    UINT8 ClflushLineSize;
    UINT8 MaxAddressableIds;
    UINT8 InitialApicId;
  } CpuidAdditionalInformation;

  /**
   * @brief When CPUID executes with EAX set to 01H, feature information is returned in ECX and EDX
   */
  union
  {
    struct
    {
      UINT32 StreamingSimdExtensions3                              : 1;
      UINT32 PclmulqdqInstruction                                  : 1;
      UINT32 DsArea64BitLayout                                     : 1;
      UINT32 MonitorMwaitInstruction                               : 1;
      UINT32 CplQualifiedDebugStore                                : 1;
      UINT32 VirtualMachineExtensions                              : 1;
      UINT32 SaferModeExtensions                                   : 1;
      UINT32 EnhancedIntelSpeedstepTechnology                      : 1;
      UINT32 ThermalMonitor2                                       : 1;
      UINT32 SupplementalStreamingSimdExtensions3                  : 1;
      UINT32 L1ContextId                                           : 1;
      UINT32 SiliconDebug                                          : 1;
      UINT32 FmaExtensions                                         : 1;
      UINT32 Cmpxchg16BInstruction                                 : 1;
      UINT32 XtprUpdateControl                                     : 1;
      UINT32 PerfmonAndDebugCapability                             : 1;
      UINT32 Reserved1                                             : 1;
      UINT32 ProcessContextIdentifiers                             : 1;
      UINT32 DirectCacheAccess                                     : 1;
      UINT32 Sse41Support                                          : 1;
      UINT32 Sse42Support                                          : 1;
      UINT32 X2ApicSupport                                         : 1;
      UINT32 MovbeInstruction                                      : 1;
      UINT32 PopcntInstruction                                     : 1;
      UINT32 TscDeadline                                           : 1;
      UINT32 AesniInstructionExtensions                            : 1;
      UINT32 XsaveXrstorInstruction                                : 1;
      UINT32 OsxSave                                               : 1;
      UINT32 AvxSupport                                            : 1;
      UINT32 HalfPrecisionConversionInstructions                   : 1;
      UINT32 RdrandInstruction                                     : 1;
    };

    UINT32 Flags;
  } CpuidFeatureInformationEcx;

  /**
   * @brief When CPUID executes with EAX set to 01H, feature information is returned in ECX and EDX
   */
  union
  {
    struct
    {
      UINT32 FloatingPointUnitOnChip                               : 1;
      UINT32 Virtual8086ModeEnhancements                           : 1;
      UINT32 DebuggingExtensions                                   : 1;
      UINT32 PageSizeExtension                                     : 1;
      UINT32 TimestampCounter                                      : 1;
      UINT32 RdmsrWrmsrInstructions                                : 1;
      UINT32 PhysicalAddressExtension                              : 1;
      UINT32 MachineCheckException                                 : 1;
      UINT32 Cmpxchg8B                                             : 1;
      UINT32 ApicOnChip                                            : 1;
      UINT32 Reserved1                                             : 1;
      UINT32 SysenterSysexitInstructions                           : 1;
      UINT32 MemoryTypeRangeRegisters                              : 1;
      UINT32 PageGlobalBit                                         : 1;
      UINT32 MachineCheckArchitecture                              : 1;
      UINT32 ConditionalMoveInstructions                           : 1;
      UINT32 PageAttributeTable                                    : 1;
      UINT32 PageSizeExtension36Bit                                : 1;
      UINT32 ProcessorSerialNumber                                 : 1;
      UINT32 Clflush                                               : 1;
      UINT32 Reserved2                                             : 1;
      UINT32 DebugStore                                            : 1;
      UINT32 ThermalControlMsrsForAcpi                             : 1;
      UINT32 MmxSupport                                            : 1;
      UINT32 FxsaveFxrstorInstructions                             : 1;
      UINT32 SseSupport                                            : 1;
      UINT32 Sse2Support                                           : 1;
      UINT32 SelfSnoop                                             : 1;
      UINT32 HyperThreadingTechnology                              : 1;
      UINT32 ThermalMonitor                                        : 1;
      UINT32 Reserved3                                             : 1;
      UINT32 PendingBreakEnable                                    : 1;
    };

    UINT32 Flags;
  } CpuidFeatureInformationEdx;

} CPUID_EAX_01;

/**
 * @brief Deterministic Cache Parameters Leaf
 *
 * When CPUID executes with EAX set to 04H and ECX contains an index value, the processor returns encoded data that
 * describe a set of deterministic cache parameters (for the cache level associated with the input in ECX). Valid index
 * values start from 0.
 * Software can enumerate the deterministic cache parameters for each level of the cache hierarchy starting with an index
 * value of 0, until the parameters report the value associated with the cache type field is 0. The architecturally defined
 * fields reported by deterministic cache parameters are documented in Table 3-8.
 * This Cache Size in Bytes
 * - = (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
 * - = (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
 * The CPUID leaf 04H also reports data that can be used to derive the topology of processor cores in a physical package.
 * This information is constant for all valid index values. Software can query the raw data reported by executing CPUID
 * with EAX=04H and ECX=0 and use it as part of the topology enumeration algorithm.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 CacheTypeField                                        : 5;
      UINT32 CacheLevel                                            : 3;
      UINT32 SelfInitializingCacheLevel                            : 1;
      UINT32 FullyAssociativeCache                                 : 1;
      UINT32 Reserved1                                             : 4;
      UINT32 MaxAddressableIdsForLogicalProcessorsSharingThisCache : 12;
      UINT32 MaxAddressableIdsForProcessorCoresInPhysicalPackage   : 6;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 SystemCoherencyLineSize                               : 12;
      UINT32 PhysicalLinePartitions                                : 10;
      UINT32 WaysOfAssociativity                                   : 10;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 NumberOfSets                                          : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 WriteBackInvalidate                                   : 1;
      UINT32 CacheInclusiveness                                    : 1;
      UINT32 ComplexCacheIndexing                                  : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_04;

/**
 * @brief MONITOR/MWAIT Leaf
 *
 * When CPUID executes with EAX set to 05H, the processor returns information about features available to MONITOR/MWAIT
 * instructions. The MONITOR instruction is used for address-range monitoring in conjunction with MWAIT instruction. The
 * MWAIT instruction optionally provides additional extensions for advanced power management.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 SmallestMonitorLineSize                               : 16;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 LargestMonitorLineSize                                : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 EnumerationOfMonitorMwaitExtensions                   : 1;
      UINT32 SupportsTreatingInterruptsAsBreakEventForMwait        : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 NumberOfC0SubCStates                                  : 4;
      UINT32 NumberOfC1SubCStates                                  : 4;
      UINT32 NumberOfC2SubCStates                                  : 4;
      UINT32 NumberOfC3SubCStates                                  : 4;
      UINT32 NumberOfC4SubCStates                                  : 4;
      UINT32 NumberOfC5SubCStates                                  : 4;
      UINT32 NumberOfC6SubCStates                                  : 4;
      UINT32 NumberOfC7SubCStates                                  : 4;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_05;

/**
 * @brief Thermal and Power Management Leaf
 *
 * When CPUID executes with EAX set to 06H, the processor returns information about thermal and power management features.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 TemperatureSensorSupported                            : 1;
      UINT32 IntelTurboBoostTechnologyAvailable                    : 1;
      UINT32 ApicTimerAlwaysRunning                                : 1;
      UINT32 Reserved1                                             : 1;
      UINT32 PowerLimitNotification                                : 1;
      UINT32 ClockModulationDuty                                   : 1;
      UINT32 PackageThermalManagement                              : 1;
      UINT32 HwpBaseRegisters                                      : 1;
      UINT32 HwpNotification                                       : 1;
      UINT32 HwpActivityWindow                                     : 1;
      UINT32 HwpEnergyPerformancePreference                        : 1;
      UINT32 HwpPackageLevelRequest                                : 1;
      UINT32 Reserved2                                             : 1;
      UINT32 Hdc                                                   : 1;
      UINT32 IntelTurboBoostMaxTechnology3Available                : 1;
      UINT32 HwpCapabilities                                       : 1;
      UINT32 HwpPeciOverride                                       : 1;
      UINT32 FlexibleHwp                                           : 1;
      UINT32 FastAccessModeForHwpRequestMsr                        : 1;
      UINT32 Reserved3                                             : 1;
      UINT32 IgnoringIdleLogicalProcessorHwpRequest                : 1;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 NumberOfInterruptThresholdsInThermalSensor            : 4;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 HardwareCoordinationFeedbackCapability                : 1;
      UINT32 Reserved1                                             : 2;
      UINT32 PerformanceEnergyBiasPreference                       : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_06;

/**
 * @brief Structured Extended Feature Flags Enumeration Leaf (Output depends on ECX input value)
 *
 * When CPUID executes with EAX set to 07H and ECX = 0, the processor returns information about the maximum input value for
 * sub-leaves that contain extended feature flags.
 * When CPUID executes with EAX set to 07H and the input value of ECX is invalid (see leaf 07H entry in Table 3-8), the
 * processor returns 0 in EAX/EBX/ECX/EDX. In subleaf 0, EAX returns the maximum input value of the highest leaf 7
 * sub-leaf, and EBX, ECX & EDX contain information of extended feature flags.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 NumberOfSubLeaves                                     : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Fsgsbase                                              : 1;
      UINT32 Ia32TscAdjustMsr                                      : 1;
      UINT32 Sgx                                                   : 1;
      UINT32 Bmi1                                                  : 1;
      UINT32 Hle                                                   : 1;
      UINT32 Avx2                                                  : 1;
      UINT32 FdpExcptnOnly                                         : 1;
      UINT32 Smep                                                  : 1;
      UINT32 Bmi2                                                  : 1;
      UINT32 EnhancedRepMovsbStosb                                 : 1;
      UINT32 Invpcid                                               : 1;
      UINT32 Rtm                                                   : 1;
      UINT32 RdtM                                                  : 1;
      UINT32 Deprecates                                            : 1;
      UINT32 Mpx                                                   : 1;
      UINT32 Rdt                                                   : 1;
      UINT32 Avx512F                                               : 1;
      UINT32 Avx512Dq                                              : 1;
      UINT32 Rdseed                                                : 1;
      UINT32 Adx                                                   : 1;
      UINT32 Smap                                                  : 1;
      UINT32 Avx512Ifma                                            : 1;
      UINT32 Reserved1                                             : 1;
      UINT32 Clflushopt                                            : 1;
      UINT32 Clwb                                                  : 1;
      UINT32 Intel                                                 : 1;
      UINT32 Avx512Pf                                              : 1;
      UINT32 Avx512Er                                              : 1;
      UINT32 Avx512Cd                                              : 1;
      UINT32 Sha                                                   : 1;
      UINT32 Avx512Bw                                              : 1;
      UINT32 Avx512Vl                                              : 1;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Prefetchwt1                                           : 1;
      UINT32 Avx512Vbmi                                            : 1;
      UINT32 Umip                                                  : 1;
      UINT32 Pku                                                   : 1;
      UINT32 Ospke                                                 : 1;
      UINT32 Reserved1                                             : 12;
      UINT32 Mawau                                                 : 5;
      UINT32 Rdpid                                                 : 1;
      UINT32 Reserved2                                             : 7;
      UINT32 SgxLc                                                 : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_07;

/**
 * @brief Direct Cache Access Information Leaf
 *
 * When CPUID executes with EAX set to 09H, the processor returns information about Direct Cache Access capabilities.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Ia32PlatformDcaCap                                    : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_09;

/**
 * @brief Architectural Performance Monitoring Leaf
 *
 * When CPUID executes with EAX set to 0AH, the processor returns information about support for architectural performance
 * monitoring capabilities. Architectural performance monitoring is supported if the version ID is greater than Pn 0. For
 * each version of architectural performance monitoring capability, software must enumerate this leaf to discover the
 * programming facilities and the architectural performance events available in the processor.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 VersionIdOfArchitecturalPerformanceMonitoring         : 8;
      UINT32 NumberOfPerformanceMonitoringCounterPerLogicalProcessor: 8;
      UINT32 BitWidthOfPerformanceMonitoringCounter                : 8;
      UINT32 EbxBitVectorLength                                    : 8;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 CoreCycleEventNotAvailable                            : 1;
      UINT32 InstructionRetiredEventNotAvailable                   : 1;
      UINT32 ReferenceCyclesEventNotAvailable                      : 1;
      UINT32 LastLevelCacheReferenceEventNotAvailable              : 1;
      UINT32 LastLevelCacheMissesEventNotAvailable                 : 1;
      UINT32 BranchInstructionRetiredEventNotAvailable             : 1;
      UINT32 BranchMispredictRetiredEventNotAvailable              : 1;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 NumberOfFixedFunctionPerformanceCounters              : 5;
      UINT32 BitWidthOfFixedFunctionPerformanceCounters            : 8;
      UINT32 Reserved1                                             : 2;
      UINT32 AnyThreadDeprecation                                  : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0A;

/**
 * @brief Extended Topology Enumeration Leaf
 *
 * When CPUID executes with EAX set to 0BH, the processor returns information about extended topology enumeration data.
 * Software must detect the presence of CPUID leaf 0BH by verifying
 * - the highest leaf index supported by CPUID is >= 0BH, and
 * - CPUID.0BH:EBX[15:0] reports a non-zero value.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 X2ApicIdToUniqueTopologyIdShift                       : 5;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 NumberOfLogicalProcessorsAtThisLevelType              : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 LevelNumber                                           : 8;
      UINT32 LevelType                                             : 8;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 X2ApicId                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0B;

/**
 * @defgroup CPUID_EAX_0D \
 *           EAX = 0x0D
 *
 * When CPUID executes with EAX set to 0DH and ECX = 0, the processor returns information about the bit-vector
 * representation of all processor state extensions that are supported in the processor and storage size requirements of
 * the XSAVE/XRSTOR area.
 * When CPUID executes with EAX set to 0DH and ECX = n (n > 1, and is a valid sub-leaf index), the processor returns
 * information about the size and offset of each processor extended state save area within the XSAVE/XRSTOR area. Software
 * can use the forward-extendable technique depicted below to query the valid sub-leaves and obtain size and offset
 * information for each processor extended state save area:
 * <pre> For i = 2 to 62 // sub-leaf 1 is reserved IF (CPUID.(EAX=0DH, ECX=0):VECTOR[i] = 1) // VECTOR is the 64-bit value
 * of EDX:EAX Execute CPUID.(EAX=0DH, ECX = i) to examine size and offset for sub-leaf i; FI; </pre>
 * @{
 */
/**
 * @brief Processor Extended State Enumeration Main Leaf (EAX = 0DH, ECX = 0)
 */
typedef struct
{
  /**
   * @brief Reports the supported bits of the lower 32 bits of XCR0. XCR0[n] can be set to 1 only if EAX[n] is 1
   */
  union
  {
    struct
    {
      UINT32 X87State                                              : 1;
      UINT32 SseState                                              : 1;
      UINT32 AvxState                                              : 1;
      UINT32 MpxState                                              : 2;
      UINT32 Avx512State                                           : 3;
      UINT32 UsedForIa32Xss1                                       : 1;
      UINT32 PkruState                                             : 1;
      UINT32 Reserved1                                             : 3;
      UINT32 UsedForIa32Xss2                                       : 1;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 MaxSizeRequiredByEnabledFeaturesInXcr0                : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 MaxSizeOfXsaveXrstorSaveArea                          : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Xcr0SupportedBits                                     : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_00;

/**
 * @brief Direct Cache Access Information Leaf
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;
      UINT32 SupportsXsavecAndCompactedXrstor                      : 1;
      UINT32 SupportsXgetbvWithEcx1                                : 1;
      UINT32 SupportsXsaveXrstorAndIa32Xss                         : 1;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 SizeOfXsaveAread                                      : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 UsedForXcr01                                          : 8;
      UINT32 PtState                                               : 1;
      UINT32 UsedForXcr02                                          : 1;
      UINT32 Reserved1                                             : 3;
      UINT32 HwpState                                              : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_01;

/**
 * @brief Processor Extended State Enumeration Sub-leaves (EAX = 0DH, ECX = n, n > 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Ia32PlatformDcaCap                                    : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Ecx2                                                  : 1;
      UINT32 Ecx1                                                  : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0D_ECX_N;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_0F \
 *           EAX = 0x0F
 *
 * When CPUID executes with EAX set to 0FH and ECX = 0, the processor returns information about the bit-vector
 * representation of QoS monitoring resource types that are supported in the processor and maximum range of RMID values the
 * processor can use to monitor of any supported resource types. Each bit, starting from bit 1, corresponds to a specific
 * resource type if the bit is set. The bit position corresponds to the sub-leaf index (or ResID) that software must use to
 * query QoS monitoring capability available for that type. See Table 3-8.
 * When CPUID executes with EAX set to 0FH and ECX = n (n >= 1, and is a valid ResID), the processor returns information
 * software can use to program IA32_PQR_ASSOC, IA32_QM_EVTSEL MSRs before reading QoS data from the IA32_QM_CTR MSR.
 * @{
 */
/**
 * @brief Intel Resource Director Technology (Intel RDT) Monitoring Enumeration Sub-leaf (EAX = 0FH, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 RmidMaxRange                                          : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;
      UINT32 SupportsL3CacheIntelRdtMonitoring                     : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0F_ECX_00;

/**
 * @brief L3 Cache Intel RDT Monitoring Capability Enumeration Sub-leaf (EAX = 0FH, ECX = 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ConversionFactor                                      : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 RmidMaxRange                                          : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 SupportsL3OccupancyMonitoring                         : 1;
      UINT32 SupportsL3TotalBandwidthMonitoring                    : 1;
      UINT32 SupportsL3LocalBandwidthMonitoring                    : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_0F_ECX_01;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_10 \
 *           EAX = 0x10
 *
 * When CPUID executes with EAX set to 10H and ECX = 0, the processor returns information about the bit-vector
 * representation of QoS Enforcement resource types that are supported in the processor. Each bit, starting from bit 1,
 * corresponds to a specific resource type if the bit is set. The bit position corresponds to the sub-leaf index (or ResID)
 * that software must use to query QoS enforcement capability available for that type.
 * When CPUID executes with EAX set to 10H and ECX = n (n >= 1, and is a valid ResID), the processor returns information
 * about available classes of service and range of QoS mask MSRs that software can use to configure each class of services
 * using capability bit masks in the QoS Mask registers, IA32_resourceType_Mask_n.
 * @{
 */
/**
 * @brief Intel Resource Director Technology (Intel RDT) Allocation Enumeration Sub-leaf (EAX = 10H, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Ia32PlatformDcaCap                                    : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 1;
      UINT32 SupportsL3CacheAllocationTechnology                   : 1;
      UINT32 SupportsL2CacheAllocationTechnology                   : 1;
      UINT32 SupportsMemoryBandwidthAllocation                     : 1;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_00;

/**
 * @brief L3 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 LengthOfCapacityBitMask                               : 5;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Ebx0                                                  : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 2;
      UINT32 CodeAndDataPriorizationTechnologySupported            : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 HighestCosNumberSupported                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_01;

/**
 * @brief L2 Cache Allocation Technology Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 2)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 LengthOfCapacityBitMask                               : 5;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Ebx0                                                  : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 HighestCosNumberSupported                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_02;

/**
 * @brief Memory Bandwidth Allocation Enumeration Sub-leaf (EAX = 10H, ECX = ResID = 3)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 MaxMbaThrottlingValue                                 : 12;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 2;
      UINT32 ResponseOfDelayIsLinear                               : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 HighestCosNumberSupported                             : 16;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_10_ECX_03;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_12 \
 *           EAX = 0x12
 *
 * When CPUID executes with EAX set to 12H and ECX = 0H, the processor returns information about Intel SGX capabilities.
 * When CPUID executes with EAX set to 12H and ECX = 1H, the processor returns information about Intel SGX attributes.
 * When CPUID executes with EAX set to 12H and ECX = n (n > 1), the processor returns information about Intel SGX Enclave
 * Page Cache.
 * @{
 */
/**
 * @brief Intel SGX Capability Enumeration Leaf, sub-leaf 0 (EAX = 12H, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Sgx1                                                  : 1;
      UINT32 Sgx2                                                  : 1;
      UINT32 Reserved1                                             : 3;
      UINT32 SgxEnclvAdvanced                                      : 1;
      UINT32 SgxEnclsAdvanced                                      : 1;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Miscselect                                            : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 MaxEnclaveSizeNot64                                   : 8;
      UINT32 MaxEnclaveSize64                                      : 8;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_00;

/**
 * @brief Intel SGX Attributes Enumeration Leaf, sub-leaf 1 (EAX = 12H, ECX = 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 ValidSecsAttributes0                                  : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ValidSecsAttributes1                                  : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 ValidSecsAttributes2                                  : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 ValidSecsAttributes3                                  : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_01;

/**
 * @brief Intel SGX EPC Enumeration Leaf, sub-leaves (EAX = 12H, ECX = 2 or higher)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 SubLeafType                                           : 4;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Zero                                                  : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Zero                                                  : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Zero                                                  : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_02P_SLT_0;

/**
 * @brief Intel SGX EPC Enumeration Leaf, sub-leaves (EAX = 12H, ECX = 2 or higher)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 SubLeafType                                           : 4;
      UINT32 Reserved1                                             : 8;
      UINT32 EpcBasePhysicalAddress1                               : 20;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 EpcBasePhysicalAddress2                               : 20;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 EpcSectionProperty                                    : 4;
      UINT32 Reserved1                                             : 8;
      UINT32 EpcSize1                                              : 20;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 EpcSize2                                              : 20;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_12_ECX_02P_SLT_1;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_14 \
 *           EAX = 0x14
 *
 * When CPUID executes with EAX set to 14H and ECX = 0H, the processor returns information about Intel Processor Trace
 * extensions.
 * When CPUID executes with EAX set to 14H and ECX = n (n > 0 and less than the number of non-zero bits in CPUID.(EAX=14H,
 * ECX= 0H).EAX), the processor returns information about packet generation in Intel Processor Trace.
 * @{
 */
/**
 * @brief Intel Processor Trace Enumeration Main Leaf (EAX = 14H, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 MaxSubLeaf                                            : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Flag0                                                 : 1;
      UINT32 Flag1                                                 : 1;
      UINT32 Flag2                                                 : 1;
      UINT32 Flag3                                                 : 1;
      UINT32 Flag4                                                 : 1;
      UINT32 Flag5                                                 : 1;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Flag0                                                 : 1;
      UINT32 Flag1                                                 : 1;
      UINT32 Flag2                                                 : 1;
      UINT32 Flag3                                                 : 1;
      UINT32 Reserved1                                             : 27;
      UINT32 Flag31                                                : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_14_ECX_00;

/**
 * @brief Intel Processor Trace Enumeration Sub-leaf (EAX = 14H, ECX = 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 NumberOfConfigurableAddressRangesForFiltering         : 3;
      UINT32 Reserved1                                             : 13;
      UINT32 BitmapOfSupportedMtcPeriodEncodings                   : 16;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 BitmapOfSupportedCycleThresholdValueEncodings         : 16;
      UINT32 BitmapOfSupportedConfigurablePsbFrequencyEncodings    : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_14_ECX_01;

/**
 * @}
 */

/**
 * @brief Stamp Counter and Nominal Core Crystal Clock Information Leaf
 *
 * When CPUID executes with EAX set to 15H and ECX = 0H, the processor returns information about Time Stamp Counter and
 * Core Crystal Clock.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Denominator                                           : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Numerator                                             : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 NominalFrequency                                      : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_15;

/**
 * @brief Processor Frequency Information Leaf
 *
 * When CPUID executes with EAX set to 16H, the processor returns information about Processor Frequency Information.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 ProcesorBaseFrequencyMhz                              : 16;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ProcessorMaximumFrequencyMhz                          : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 BusFrequencyMhz                                       : 16;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_16;

/**
 * @defgroup CPUID_EAX_17 \
 *           EAX = 0x17
 *
 * When CPUID executes with EAX set to 17H, the processor returns information about the System-On-Chip Vendor Attribute
 * Enumeration.
 * @{
 */
/**
 * @brief System-On-Chip Vendor Attribute Enumeration Main Leaf (EAX = 17H, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 MaxSocIdIndex                                         : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 SocVendorId                                           : 16;
      UINT32 IsVendorScheme                                        : 1;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 ProjectId                                             : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 SteppingId                                            : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_00;

/**
 * @brief System-On-Chip Vendor Attribute Enumeration Sub-leaf (EAX = 17H, ECX = 1..3)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 SocVendorBrandString                                  : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 SocVendorBrandString                                  : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 SocVendorBrandString                                  : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 SocVendorBrandString                                  : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_01_03;

/**
 * @brief System-On-Chip Vendor Attribute Enumeration Sub-leaves (EAX = 17H, ECX > MaxSOCID_Index)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_17_ECX_N;

/**
 * @}
 */

/**
 * @defgroup CPUID_EAX_18 \
 *           EAX = 0x18
 *
 * When CPUID executes with EAX set to 18H, the processor returns information about the Deterministic Address Translation
 * Parameters.
 * @{
 */
/**
 * @brief Deterministic Address Translation Parameters Main Leaf (EAX = 18H, ECX = 0)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 MaxSubLeaf                                            : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 PageEntries4KbSupported                               : 1;
      UINT32 PageEntries2MbSupported                               : 1;
      UINT32 PageEntries4MbSupported                               : 1;
      UINT32 PageEntries1GbSupported                               : 1;
      UINT32 Reserved1                                             : 4;
      UINT32 Partitioning                                          : 3;
      UINT32 Reserved2                                             : 5;
      UINT32 WaysOfAssociativity00                                 : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 NumberOfSets                                          : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 TranslationCacheTypeField                             : 5;
      UINT32 TranslationCacheLevel                                 : 3;
      UINT32 FullyAssociativeStructure                             : 1;
      UINT32 Reserved1                                             : 5;
      UINT32 MaxAddressableIdsForLogicalProcessors                 : 12;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_18_ECX_00;

/**
 * @brief Deterministic Address Translation Parameters Sub-leaf (EAX = 18H, ECX >= 1)
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 PageEntries4KbSupported                               : 1;
      UINT32 PageEntries2MbSupported                               : 1;
      UINT32 PageEntries4MbSupported                               : 1;
      UINT32 PageEntries1GbSupported                               : 1;
      UINT32 Reserved1                                             : 4;
      UINT32 Partitioning                                          : 3;
      UINT32 Reserved2                                             : 5;
      UINT32 WaysOfAssociativity01                                 : 16;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 NumberOfSets                                          : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 TranslationCacheTypeField                             : 5;
      UINT32 TranslationCacheLevel                                 : 3;
      UINT32 FullyAssociativeStructure                             : 1;
      UINT32 Reserved1                                             : 5;
      UINT32 MaxAddressableIdsForLogicalProcessors                 : 12;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_18_ECX_01P;

/**
 * @}
 */

/**
 * @brief Extended Function CPUID Information
 *
 * When CPUID executes with EAX set to 80000000H, the processor returns the highest value the processor recognizes for
 * returning extended processor information. The value is returned in the EAX register and is processor specific.
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 MaxExtendedFunctions                                  : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000000;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 LahfSahfAvailableIn64BitMode                          : 1;
      UINT32 Reserved1                                             : 4;
      UINT32 Lzcnt                                                 : 1;
      UINT32 Reserved2                                             : 2;
      UINT32 Prefetchw                                             : 1;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 11;
      UINT32 SyscallSysretAvailableIn64BitMode                     : 1;
      UINT32 Reserved2                                             : 8;
      UINT32 ExecuteDisableBitAvailable                            : 1;
      UINT32 Reserved3                                             : 5;
      UINT32 Pages1GbAvailable                                     : 1;
      UINT32 RdtscpAvailable                                       : 1;
      UINT32 Reserved4                                             : 1;
      UINT32 Ia64Available                                         : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000001;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 ProcessorBrandString1                                 : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString2                                 : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString3                                 : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString4                                 : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000002;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 ProcessorBrandString5                                 : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString6                                 : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString7                                 : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString8                                 : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000003;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 ProcessorBrandString9                                 : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString10                                : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString11                                : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 ProcessorBrandString12                                : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000004;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000005;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 CacheLineSizeInBytes                                  : 8;
      UINT32 Reserved1                                             : 4;
      UINT32 L2AssociativityField                                  : 4;
      UINT32 CacheSizeIn1KUnits                                    : 16;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000006;

/**
 * @brief Extended Function CPUID Information
 */
typedef struct
{
  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Eax;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ebx;

  union
  {
    struct
    {
      UINT32 Reserved                                              : 32;
    };

    UINT32 Flags;
  } Ecx;

  union
  {
    struct
    {
      UINT32 Reserved1                                             : 8;
      UINT32 InvariantTscAvailable                                 : 1;
    };

    UINT32 Flags;
  } Edx;

} CPUID_EAX_80000007;

/**
 * @}
 */

/**
 * @defgroup MODEL_SPECIFIC_REGISTERS \
 *           Model Specific Registers
 *
 * @see Vol2A[3.2(CPUID)] (reference)
 * @{
 */
/**
 * @defgroup IA32_P5_MC \
 *           IA32_P5_MC_(x)
 *
 * When machine-check exceptions are enabled for the Pentium processor (MCE flag is set in control register CR4), the
 * machine-check exception handler uses the RDMSR instruction to read the error type from the P5_MC_TYPE register and the
 * machine check address from the P5_MC_ADDR register. The handler then normally reports these register values to the
 * system console before aborting execution.
 *
 * @see Vol3B[15.10.2(Pentium Processor Machine-Check Exception Handling)] (reference)
 * @{
 */
/**
 * @brief Machine-check exception address.
 */
#define IA32_P5_MC_ADDR                                              0x00000000

/**
 * @brief Machine-check exception type.
 */
#define IA32_P5_MC_TYPE                                              0x00000001

/**
 * @}
 */

/**
 * @brief System coherence line size.
 */
#define IA32_MONITOR_FILTER_LINE_SIZE                                0x00000006

/**
 * @brief Value as returned by instruction RDTSC. <b>(R/W)</b>
 */
#define IA32_TIME_STAMP_COUNTER                                      0x00000010

/**
 * @brief The operating system can use this MSR to determine "slot" information for the processor and the proper microcode
 *        update to load. <b>(RO)</b>
 */
#define IA32_PLATFORM_ID                                             0x00000017

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 50;
    UINT64 PlatformId                                              : 3;
  };

  UINT64 Flags;
} IA32_PLATFORM_ID_REGISTER;

/**
 * @brief This register holds the APIC base address, permitting the relocation of the APIC memory map.
 */
#define IA32_APIC_BASE                                               0x0000001B

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 8;
    UINT64 BspFlag                                                 : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 EnableX2ApicMode                                        : 1;
    UINT64 ApicGlobalEnable                                        : 1;
    UINT64 ApicBase                                                : 36;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_APIC_BASE_REGISTER;

/**
 * @brief Control Features in Intel 64 Processor. <b>(R/W)</b>
 */
#define IA32_FEATURE_CONTROL                                         0x0000003A

typedef union
{
  struct
  {
    UINT64 LockBit                                                 : 1;
    UINT64 EnableVmxInsideSmx                                      : 1;
    UINT64 EnableVmxOutsideSmx                                     : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 SenterLocalFunctionEnables                              : 7;
    UINT64 SenterGlobalEnable                                      : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 SgxLaunchControlEnable                                  : 1;
    UINT64 SgxGlobalEnable                                         : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 LmceOn                                                  : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_FEATURE_CONTROL_REGISTER;

/**
 * @brief Per Logical Processor TSC Adjust. <b>(R/Write to clear)</b>
 */
#define IA32_TSC_ADJUST                                              0x0000003B

typedef struct
{
  UINT64 ThreadAdjust;
} IA32_TSC_ADJUST_REGISTER;

/**
 * @brief Executing a WRMSR instruction to this MSR causes a microcode update to be loaded into the processor. A processor
 *        may prevent writing to this MSR when loading guest states on VM entries or saving guest states on VM exits. <b>(W)</b>
 */
#define IA32_BIOS_UPDATE_TRIGGER                                     0x00000079

/**
 * @brief Returns the microcode update signature following the execution of CPUID.01H. A processor may prevent writing to
 *        this MSR when loading guest states on VM entries or saving guest states on VM exits. <b>(RO)</b>
 */
#define IA32_BIOS_UPDATE_SIGNATURE                                   0x0000008B

typedef struct
{
  UINT32 Reserved;
  UINT32 MicrocodeUpdateSignature;
} IA32_BIOS_UPDATE_SIGNATURE_REGISTER;

/**
 * @defgroup IA32_SGXLEPUBKEYHASH \
 *           IA32_SGXLEPUBKEYHASH[(64*n+63):(64*n)]
 *
 * Bits (64*n+63):(64*n) of the SHA256 digest of the SIGSTRUCT.MODULUS for SGX Launch Enclave. On reset, the default value
 * is the digest of Intel's signing key.
 *
 * @remarks Read permitted If CPUID.(EAX=12H,ECX=0H): EAX[0]=1 && CPUID.(EAX=07H,ECX=0H):ECX[30]=1. Write permitted if
 *          CPUID.(EAX=12H,ECX=0H): EAX[0]=1 && IA32_FEATURE_CONTROL[17] = 1 && IA32_FEATURE_CONTROL[0] = 1.
 * @{
 */
#define IA32_SGXLEPUBKEYHASH0                                        0x0000008C
#define IA32_SGXLEPUBKEYHASH1                                        0x0000008D
#define IA32_SGXLEPUBKEYHASH2                                        0x0000008E
#define IA32_SGXLEPUBKEYHASH3                                        0x0000008F
/**
 * @}
 */

/**
 * @brief SMM Monitor Configuration. <b>(R/W)</b>
 */
#define IA32_SMM_MONITOR_CTL                                         0x0000009B

typedef union
{
  struct
  {
    UINT64 Valid                                                   : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 SmiUnblockingByVmxoff                                   : 1;
    UINT64 Reserved2                                               : 9;
    UINT64 MsegBase                                                : 20;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMM_MONITOR_CTL_REGISTER;

typedef struct
{
  UINT32 MsegHeaderRevision;
  UINT32 MonitorFeatures;

  /**
   * @brief Define values for the MonitorFeatures field of MSEG_HEADER.
   */
#define IA32_STM_FEATURES_IA32E                                      0x00000001

  UINT32 GdtrLimit;
  UINT32 GdtrBaseOffset;
  UINT32 CsSelector;
  UINT32 EipOffset;
  UINT32 EspOffset;
  UINT32 Cr3Offset;
} IA32_MSEG_HEADER;

/**
 * @brief Base address of the logical processor's SMRAM image. <b>(RO, SMM only)</b>
 */
#define IA32_SMBASE                                                  0x0000009E

/**
 * @defgroup IA32_PMC \
 *           IA32_PMC(n)
 *
 * General Performance Counters.
 *
 * @remarks If CPUID.0AH: EAX[15:8] > n
 * @{
 */
#define IA32_PMC0                                                    0x000000C1
#define IA32_PMC1                                                    0x000000C2
#define IA32_PMC2                                                    0x000000C3
#define IA32_PMC3                                                    0x000000C4
#define IA32_PMC4                                                    0x000000C5
#define IA32_PMC5                                                    0x000000C6
#define IA32_PMC6                                                    0x000000C7
#define IA32_PMC7                                                    0x000000C8
/**
 * @}
 */

/**
 * @brief TSC Frequency Clock Counter. <b>(R/Write to clear)</b>
 */
#define IA32_MPERF                                                   0x000000E7

typedef struct
{
  UINT64 C0Mcnt;
} IA32_MPERF_REGISTER;

/**
 * @brief Actual Performance Clock Counter <b>(R/Write to clear)</b>
 */
#define IA32_APERF                                                   0x000000E8

typedef struct
{
  UINT64 C0Acnt;
} IA32_APERF_REGISTER;

/**
 * @brief MTRR Capability. <b>(RO)</b>
 */
#define IA32_MTRR_CAPABILITIES                                       0x000000FE

typedef union
{
  struct
  {
    UINT64 VariableRangeCount                                      : 8;
    UINT64 FixedRangeSupported                                     : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 WcSupported                                             : 1;
    UINT64 SmrrSupported                                           : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MTRR_CAPABILITIES_REGISTER;

/**
 * @brief The lower 16 bits of this MSR are the segment selector for the privilege level 0 code segment. This value is also
 *        used to determine the segment selector of the privilege level 0 stack segment. This value cannot indicate a null
 *        selector. <b>(R/W)</b>
 */
#define IA32_SYSENTER_CS                                             0x00000174

typedef struct
{
  UINT16 CsSelector;
  UINT16 NotUsed1;
  UINT32 NotUsed2;
} IA32_SYSENTER_CS_REGISTER;

/**
 * @brief The value of this MSR is loaded into RSP (thus, this value contains the stack pointer for the privilege level 0
 *        stack). This value cannot represent a non-canonical address. In protected mode, only bits 31:0 are loaded. <b>(R/W)</b>
 */
#define IA32_SYSENTER_ESP                                            0x00000175

/**
 * @brief The value of this MSR is loaded into RIP (thus, this value references the first instruction of the selected
 *        operating procedure or routine). In protected mode, only bits 31:0 are loaded. <b>(R/W)</b>
 */
#define IA32_SYSENTER_EIP                                            0x00000176

/**
 * @brief Global Machine Check Capability. <b>(RO)</b>
 */
#define IA32_MCG_CAP                                                 0x00000179

typedef union
{
  struct
  {
    UINT64 Count                                                   : 8;
    UINT64 McgCtlP                                                 : 1;
    UINT64 McgExtP                                                 : 1;
    UINT64 McpCmciP                                                : 1;
    UINT64 McgTesP                                                 : 1;
    UINT64 Reserved1                                               : 4;
    UINT64 McgExtCnt                                               : 8;
    UINT64 McgSerP                                                 : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 McgElogP                                                : 1;
    UINT64 McgLmceP                                                : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MCG_CAP_REGISTER;

/**
 * @brief Global Machine Check Status. <b>(R/W0)</b>
 */
#define IA32_MCG_STATUS                                              0x0000017A

typedef union
{
  struct
  {
    UINT64 Ripv                                                    : 1;
    UINT64 Eipv                                                    : 1;
    UINT64 Mcip                                                    : 1;
    UINT64 LmceS                                                   : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MCG_STATUS_REGISTER;

/**
 * @brief Global Machine Check Control. <b>(R/W)</b>
 */
#define IA32_MCG_CTL                                                 0x0000017B

/**
 * @defgroup IA32_PERFEVTSEL \
 *           IA32_PERFEVTSEL(n)
 *
 * Performance Event Select Register n.
 *
 * @remarks If CPUID.0AH: EAX[15:8] > n
 * @{
 */
#define IA32_PERFEVTSEL0                                             0x00000186
#define IA32_PERFEVTSEL1                                             0x00000187
#define IA32_PERFEVTSEL2                                             0x00000188
#define IA32_PERFEVTSEL3                                             0x00000189
typedef union
{
  struct
  {
    UINT64 EventSelect                                             : 8;
    UINT64 UMask                                                   : 8;
    UINT64 Usr                                                     : 1;
    UINT64 Os                                                      : 1;
    UINT64 Edge                                                    : 1;
    UINT64 Pc                                                      : 1;
    UINT64 Int                                                     : 1;
    UINT64 AnyThread                                               : 1;
    UINT64 En                                                      : 1;
    UINT64 Inv                                                     : 1;
    UINT64 Cmask                                                   : 8;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERFEVTSEL_REGISTER;

/**
 * @}
 */

/**
 * @brief Current Performance Status. <b>(RO)</b>
 */
#define IA32_PERF_STATUS                                             0x00000198

typedef struct
{
  UINT16 StateValue;
} IA32_PERF_STATUS_REGISTER;

/**
 * @brief Performance Control. Software makes a request for a new Performance state (P-State) by writing this MSR. <b>(R/W)</b>
 */
#define IA32_PERF_CTL                                                0x00000199

typedef union
{
  struct
  {
    UINT64 TargetStateValue                                        : 16;
    UINT64 Reserved1                                               : 16;
    UINT64 IdaEngage                                               : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERF_CTL_REGISTER;

/**
 * @brief Clock Modulation Control. <b>(R/W)</b>
 */
#define IA32_CLOCK_MODULATION                                        0x0000019A

typedef union
{
  struct
  {
    UINT64 ExtendedOnDemandClockModulationDutyCycle                : 1;
    UINT64 OnDemandClockModulationDutyCycle                        : 3;
    UINT64 OnDemandClockModulationEnable                           : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_CLOCK_MODULATION_REGISTER;

/**
 * @brief Thermal Interrupt Control. Enables and disables the generation of an interrupt on temperature transitions
 *        detected with the processor's thermal sensors and thermal monitor. <b>(R/W)</b>
 */
#define IA32_THERM_INTERRUPT                                         0x0000019B

typedef union
{
  struct
  {
    UINT64 HighTemperatureInterruptEnable                          : 1;
    UINT64 LowTemperatureInterruptEnable                           : 1;
    UINT64 ProchotInterruptEnable                                  : 1;
    UINT64 ForceprInterruptEnable                                  : 1;
    UINT64 CriticalTemperatureInterruptEnable                      : 1;
    UINT64 Reserved1                                               : 3;
    UINT64 Threshold1Value                                         : 7;
    UINT64 Threshold1InterruptEnable                               : 1;
    UINT64 Threshold2Value                                         : 7;
    UINT64 Threshold2InterruptEnable                               : 1;
    UINT64 PowerLimitNotificationEnable                            : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_THERM_INTERRUPT_REGISTER;

/**
 * @brief Thermal Status Information. Contains status information about the processor's thermal sensor and automatic
 *        thermal monitoring facilities. <b>(RO)</b>
 */
#define IA32_THERM_STATUS                                            0x0000019C

typedef union
{
  struct
  {
    UINT64 ThermalStatus                                           : 1;
    UINT64 ThermalStatusLog                                        : 1;
    UINT64 ProchotForceprEvent                                     : 1;
    UINT64 ProchotForceprLog                                       : 1;
    UINT64 CriticalTemperatureStatus                               : 1;
    UINT64 CriticalTemperatureStatusLog                            : 1;
    UINT64 ThermalThreshold1Status                                 : 1;
    UINT64 ThermalThreshold1Log                                    : 1;
    UINT64 ThermalThreshold2Status                                 : 1;
    UINT64 ThermalThreshold2Log                                    : 1;
    UINT64 PowerLimitationStatus                                   : 1;
    UINT64 PowerLimitationLog                                      : 1;
    UINT64 CurrentLimitStatus                                      : 1;
    UINT64 CurrentLimitLog                                         : 1;
    UINT64 CrossDomainLimitStatus                                  : 1;
    UINT64 CrossDomainLimitLog                                     : 1;
    UINT64 DigitalReadout                                          : 7;
    UINT64 Reserved1                                               : 4;
    UINT64 ResolutionInDegreesCelsius                              : 4;
    UINT64 ReadingValid                                            : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_THERM_STATUS_REGISTER;

/**
 * @brief Allows a variety of processor functions to be enabled and disabled. <b>(R/W)</b>
 */
#define IA32_MISC_ENABLE                                             0x000001A0

typedef union
{
  struct
  {
    UINT64 FastStringsEnable                                       : 1;
    UINT64 Reserved1                                               : 2;
    UINT64 AutomaticThermalControlCircuitEnable                    : 1;
    UINT64 Reserved2                                               : 3;
    UINT64 PerformanceMonitoringAvailable                          : 1;
    UINT64 Reserved3                                               : 3;
    UINT64 BranchTraceStorageUnavailable                           : 1;
    UINT64 ProcessorEventBasedSamplingUnavailable                  : 1;
    UINT64 Reserved4                                               : 3;
    UINT64 EnhancedIntelSpeedstepTechnologyEnable                  : 1;
    UINT64 Reserved5                                               : 1;
    UINT64 EnableMonitorFsm                                        : 1;
    UINT64 Reserved6                                               : 3;
    UINT64 LimitCpuidMaxval                                        : 1;
    UINT64 XtprMessageDisable                                      : 1;
    UINT64 Reserved7                                               : 10;
    UINT64 XdBitDisable                                            : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MISC_ENABLE_REGISTER;

/**
 * @brief Performance Energy Bias Hint. <b>(R/W)</b>
 */
#define IA32_ENERGY_PERF_BIAS                                        0x000001B0

typedef union
{
  struct
  {
    UINT64 PowerPolicyPreference                                   : 4;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_ENERGY_PERF_BIAS_REGISTER;

/**
 * @brief Package Thermal Status Information. Contains status information about the package's thermal sensor. <b>(RO)</b>
 */
#define IA32_PACKAGE_THERM_STATUS                                    0x000001B1

typedef union
{
  struct
  {
    UINT64 ThermalStatus                                           : 1;
    UINT64 ThermalStatusLog                                        : 1;
    UINT64 ProchotEvent                                            : 1;
    UINT64 ProchotLog                                              : 1;
    UINT64 CriticalTemperatureStatus                               : 1;
    UINT64 CriticalTemperatureStatusLog                            : 1;
    UINT64 ThermalThreshold1Status                                 : 1;
    UINT64 ThermalThreshold1Log                                    : 1;
    UINT64 ThermalThreshold2Status                                 : 1;
    UINT64 ThermalThreshold2Log                                    : 1;
    UINT64 PowerLimitationStatus                                   : 1;
    UINT64 PowerLimitationLog                                      : 1;
    UINT64 Reserved1                                               : 4;
    UINT64 DigitalReadout                                          : 7;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PACKAGE_THERM_STATUS_REGISTER;

/**
 * @brief Enables and disables the generation of an interrupt on temperature transitions detected with the package's
 *        thermal sensor. <b>(RO)</b>
 */
#define IA32_PACKAGE_THERM_INTERRUPT                                 0x000001B2

typedef union
{
  struct
  {
    UINT64 HighTemperatureInterruptEnable                          : 1;
    UINT64 LowTemperatureInterruptEnable                           : 1;
    UINT64 ProchotInterruptEnable                                  : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 OverheatInterruptEnable                                 : 1;
    UINT64 Reserved2                                               : 3;
    UINT64 Threshold1Value                                         : 7;
    UINT64 Threshold1InterruptEnable                               : 1;
    UINT64 Threshold2Value                                         : 7;
    UINT64 Threshold2InterruptEnable                               : 1;
    UINT64 PowerLimitNotificationEnable                            : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PACKAGE_THERM_INTERRUPT_REGISTER;

/**
 * @brief Trace/Profile Resource Control. <b>(R/W)</b>
 */
#define IA32_DEBUGCTL                                                0x000001D9

typedef union
{
  struct
  {
    UINT64 Lbr                                                     : 1;
    UINT64 Btf                                                     : 1;
    UINT64 Reserved1                                               : 4;
    UINT64 Tr                                                      : 1;
    UINT64 Bts                                                     : 1;
    UINT64 Btint                                                   : 1;
    UINT64 BtsOffOs                                                : 1;
    UINT64 BtsOffUsr                                               : 1;
    UINT64 FreezeLbrsOnPmi                                         : 1;
    UINT64 FreezePerfmonOnPmi                                      : 1;
    UINT64 EnableUncorePmi                                         : 1;
    UINT64 FreezeWhileSmm                                          : 1;
    UINT64 RtmDebug                                                : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_DEBUGCTL_REGISTER;

/**
 * @brief SMRR Base Address. Base address of SMM memory range. <b>(Writeable only in SMM)</b>
 */
#define IA32_SMRR_PHYSBASE                                           0x000001F2

typedef union
{
  struct
  {
    UINT64 Type                                                    : 8;
    UINT64 Reserved1                                               : 4;
    UINT64 SmrrPhysicalBaseAddress                                 : 20;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMRR_PHYSBASE_REGISTER;

/**
 * @brief Range Mask of SMM memory range. <b>(Writeable only in SMM)</b>
 */
#define IA32_SMRR_PHYSMASK                                           0x000001F3

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 11;
    UINT64 EnableRangeMask                                         : 1;
    UINT64 SmrrAddressRangeMask                                    : 20;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_SMRR_PHYSMASK_REGISTER;

/**
 * @brief DCA Capability. <b>(R)</b>
 */
#define IA32_PLATFORM_DCA_CAP                                        0x000001F8

/**
 * @brief If set, CPU supports Prefetch-Hint type.
 */
#define IA32_CPU_DCA_CAP                                             0x000001F9

/**
 * @brief DCA type 0 Status and Control register.
 */
#define IA32_DCA_0_CAP                                               0x000001FA

typedef union
{
  struct
  {
    UINT64 DcaActive                                               : 1;
    UINT64 Transaction                                             : 2;
    UINT64 DcaType                                                 : 4;
    UINT64 DcaQueueSize                                            : 4;
    UINT64 Reserved1                                               : 2;
    UINT64 DcaDelay                                                : 4;
    UINT64 Reserved2                                               : 7;
    UINT64 SwBlock                                                 : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 HwBlock                                                 : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_DCA_0_CAP_REGISTER;

/**
 * @defgroup IA32_MTRR_PHYSBASE \
 *           IA32_MTRR_PHYSBASE(n)
 *
 * IA32_MTRR_PHYSBASE(0-9).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.3(Variable Range MTRRs)]
 * @{
 */
#define IA32_MTRR_PHYSBASE0                                          0x00000200
#define IA32_MTRR_PHYSBASE1                                          0x00000202
#define IA32_MTRR_PHYSBASE2                                          0x00000204
#define IA32_MTRR_PHYSBASE3                                          0x00000206
#define IA32_MTRR_PHYSBASE4                                          0x00000208
#define IA32_MTRR_PHYSBASE5                                          0x0000020A
#define IA32_MTRR_PHYSBASE6                                          0x0000020C
#define IA32_MTRR_PHYSBASE7                                          0x0000020E
#define IA32_MTRR_PHYSBASE8                                          0x00000210
#define IA32_MTRR_PHYSBASE9                                          0x00000212
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_PHYSMASK \
 *           IA32_MTRR_PHYSMASK(n)
 *
 * IA32_MTRR_PHYSMASK(0-9).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.3(Variable Range MTRRs)]
 * @{
 */
#define IA32_MTRR_PHYSMASK0                                          0x00000201
#define IA32_MTRR_PHYSMASK1                                          0x00000203
#define IA32_MTRR_PHYSMASK2                                          0x00000205
#define IA32_MTRR_PHYSMASK3                                          0x00000207
#define IA32_MTRR_PHYSMASK4                                          0x00000209
#define IA32_MTRR_PHYSMASK5                                          0x0000020B
#define IA32_MTRR_PHYSMASK6                                          0x0000020D
#define IA32_MTRR_PHYSMASK7                                          0x0000020F
#define IA32_MTRR_PHYSMASK8                                          0x00000211
#define IA32_MTRR_PHYSMASK9                                          0x00000213
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX \
 *           IA32_MTRR_FIX(x)
 *
 * IA32_MTRR_FIX(x).
 *
 * @remarks If CPUID.01H: EDX.MTRR[12] = 1
 * @see Vol3A[11.11.2.2(Fixed Range MTRRs)]
 * @{
 */
/**
 * @defgroup IA32_MTRR_FIX64K \
 *           IA32_MTRR_FIX64K(x)
 *
 * IA32_MTRR_FIX64K(x).
 * @{
 */
#define IA32_MTRR_FIX64K_BASE                                        0x00000000
#define IA32_MTRR_FIX64K_SIZE                                        0x00010000
#define IA32_MTRR_FIX64K_00000                                       0x00000250
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX16K \
 *           IA32_MTRR_FIX16K(x)
 *
 * IA32_MTRR_FIX16K(x).
 * @{
 */
#define IA32_MTRR_FIX16K_BASE                                        0x00080000
#define IA32_MTRR_FIX16K_SIZE                                        0x00004000
#define IA32_MTRR_FIX16K_80000                                       0x00000258
#define IA32_MTRR_FIX16K_A0000                                       0x00000259
/**
 * @}
 */

/**
 * @defgroup IA32_MTRR_FIX4K \
 *           IA32_MTRR_FIX4K(x)
 *
 * IA32_MTRR_FIX4K(x).
 * @{
 */
#define IA32_MTRR_FIX4K_BASE                                         0x000C0000
#define IA32_MTRR_FIX4K_SIZE                                         0x00001000
#define IA32_MTRR_FIX4K_C0000                                        0x00000268
#define IA32_MTRR_FIX4K_C8000                                        0x00000269
#define IA32_MTRR_FIX4K_D0000                                        0x0000026A
#define IA32_MTRR_FIX4K_D8000                                        0x0000026B
#define IA32_MTRR_FIX4K_E0000                                        0x0000026C
#define IA32_MTRR_FIX4K_E8000                                        0x0000026D
#define IA32_MTRR_FIX4K_F0000                                        0x0000026E
#define IA32_MTRR_FIX4K_F8000                                        0x0000026F
/**
 * @}
 */

/**
 * @brief Architecture defined number of fixed range MTRRs (1 for 64k, 2 for 16k, 8 for 4k).
 */
#define IA32_MTRR_FIX_COUNT                                          (1 + 2 + 8)

/**
 * @brief Architecture defined number of variable range MTRRs.
 */
#define IA32_MTRR_VARIABLE_COUNT                                     0x000000FF

/**
 * @brief A size of array to store all possible MTRRs.
 */
#define IA32_MTRR_COUNT                                              (IA32_MTRR_FIX_COUNT + IA32_MTRR_VARIABLE_COUNT)

/**
 * @}
 */

/**
 * @brief IA32_PAT. <b>(R/W)</b>
 */
#define IA32_PAT                                                     0x00000277

typedef union
{
  struct
  {
    UINT64 Pa0                                                     : 3;
    UINT64 Reserved1                                               : 5;
    UINT64 Pa1                                                     : 3;
    UINT64 Reserved2                                               : 5;
    UINT64 Pa2                                                     : 3;
    UINT64 Reserved3                                               : 5;
    UINT64 Pa3                                                     : 3;
    UINT64 Reserved4                                               : 5;
    UINT64 Pa4                                                     : 3;
    UINT64 Reserved5                                               : 5;
    UINT64 Pa5                                                     : 3;
    UINT64 Reserved6                                               : 5;
    UINT64 Pa6                                                     : 3;
    UINT64 Reserved7                                               : 5;
    UINT64 Pa7                                                     : 3;
  };

  UINT64 Flags;
} IA32_PAT_REGISTER;

/**
 * @defgroup IA32_MC_CTL2 \
 *           IA32_MC(i)_CTL2
 *
 * MSR to enable/disable CMCI capability for bank n.
 *
 * @remarks If IA32_MCG_CAP[10] = 1 && IA32_MCG_CAP[7:0] > n
 * @see Vol3B[15.3.2.5(IA32_MCi_CTL2 MSRs)]
 * @{
 */
#define IA32_MC0_CTL2                                                0x00000280
#define IA32_MC1_CTL2                                                0x00000281
#define IA32_MC2_CTL2                                                0x00000282
#define IA32_MC3_CTL2                                                0x00000283
#define IA32_MC4_CTL2                                                0x00000284
#define IA32_MC5_CTL2                                                0x00000285
#define IA32_MC6_CTL2                                                0x00000286
#define IA32_MC7_CTL2                                                0x00000287
#define IA32_MC8_CTL2                                                0x00000288
#define IA32_MC9_CTL2                                                0x00000289
#define IA32_MC10_CTL2                                               0x0000028A
#define IA32_MC11_CTL2                                               0x0000028B
#define IA32_MC12_CTL2                                               0x0000028C
#define IA32_MC13_CTL2                                               0x0000028D
#define IA32_MC14_CTL2                                               0x0000028E
#define IA32_MC15_CTL2                                               0x0000028F
#define IA32_MC16_CTL2                                               0x00000290
#define IA32_MC17_CTL2                                               0x00000291
#define IA32_MC18_CTL2                                               0x00000292
#define IA32_MC19_CTL2                                               0x00000293
#define IA32_MC20_CTL2                                               0x00000294
#define IA32_MC21_CTL2                                               0x00000295
#define IA32_MC22_CTL2                                               0x00000296
#define IA32_MC23_CTL2                                               0x00000297
#define IA32_MC24_CTL2                                               0x00000298
#define IA32_MC25_CTL2                                               0x00000299
#define IA32_MC26_CTL2                                               0x0000029A
#define IA32_MC27_CTL2                                               0x0000029B
#define IA32_MC28_CTL2                                               0x0000029C
#define IA32_MC29_CTL2                                               0x0000029D
#define IA32_MC30_CTL2                                               0x0000029E
#define IA32_MC31_CTL2                                               0x0000029F
typedef union
{
  struct
  {
    UINT64 CorrectedErrorCountThreshold                            : 15;
    UINT64 Reserved1                                               : 15;
    UINT64 CmciEn                                                  : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MC_CTL2_REGISTER;

/**
 * @}
 */

/**
 * @brief IA32_MTRR_DEF_TYPE. <b>(R/W)</b>
 */
#define IA32_MTRR_DEF_TYPE                                           0x000002FF

typedef union
{
  struct
  {
    UINT64 DefaultMemoryType                                       : 3;
    UINT64 Reserved1                                               : 7;
    UINT64 FixedRangeMtrrEnable                                    : 1;
    UINT64 MtrrEnable                                              : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_MTRR_DEF_TYPE_REGISTER;

/**
 * @defgroup IA32_FIXED_CTR \
 *           IA32_FIXED_CTR(n)
 *
 * Fixed-Function Performance Counter n.
 *
 * @remarks If CPUID.0AH: EDX[4:0] > n
 * @{
 */
/**
 * @brief Counts Instr_Retired.Any.
 */
#define IA32_FIXED_CTR0                                              0x00000309

/**
 * @brief Counts CPU_CLK_Unhalted.Core
 */
#define IA32_FIXED_CTR1                                              0x0000030A

/**
 * @brief Counts CPU_CLK_Unhalted.Ref
 */
#define IA32_FIXED_CTR2                                              0x0000030B

/**
 * @}
 */

/**
 * @brief Read Only MSR that enumerates the existence of performance monitoring features. <b>(RO)</b>
 */
#define IA32_PERF_CAPABILITIES                                       0x00000345

typedef union
{
  struct
  {
    UINT64 LbrFormat                                               : 6;
    UINT64 PebsTrap                                                : 1;
    UINT64 PebsSaveArchRegs                                        : 1;
    UINT64 PebsRecordFormat                                        : 4;
    UINT64 FreezeWhileSmmIsSupported                               : 1;
    UINT64 FullWidthCounterWrite                                   : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_PERF_CAPABILITIES_REGISTER;

/**
 * @brief Fixed-Function Performance Counter Control. Counter increments while the results of ANDing respective enable bit
 *        in IA32_PERF_GLOBAL_CTRL with the corresponding OS or USR bits in this MSR is true. <b>(R/W)</b>
 */
#define IA32_FIXED_CTR_CTRL                                          0x0000038D

typedef union
{
  struct
  {
    UINT64 En0Os                                                   : 1;
    UINT64 En0Usr                                                  : 1;
    UINT64 AnyThread0                                              : 1;
    UINT64 En0Pmi                                                  : 1;
    UINT64 En1Os                                                   : 1;
    UINT64 En1Usr                                                  : 1;
    UINT64 AnyThread1                                              : 1;
    UINT64 En1Pmi                                                  : 1;
    UINT64 En2Os                                                   : 1;
    UINT64 En2Usr                                                  : 1;
    UINT64 AnyThread2                                              : 1;
    UINT64 En2Pmi                                                  : 1;
  };

  UINT32 Flags32;
  UINT64 Flags64;
} IA32_FIXED_CTR_CTRL_REGISTER;

/**
 * @brief Global Performance Counter Status. <b>(RO)</b>
 */
#define IA32_PERF_GLOBAL_STATUS                                      0x0000038E

typedef union
{
  struct
  {
    UINT64 OvfPmc0                                                 : 1;
    UINT64 OvfPmc1                                                 : 1;
    UINT64 OvfPmc2                                                 : 1;
    UINT64 OvfPmc3                                                 : 1;
    UINT64 Reserved1                                               : 28;
    UINT64 OvfFixedctr0                                            : 1;
    UINT64 OvfFixedctr1                                            : 1;
    UINT64 OvfFixedctr2                                            : 1;
    UINT64 Reserved2                                               : 20;
    UINT64 TraceTopaPmi                                            : 1;
    UINT64 Reserved3                                               : 2;
    UINT64 LbrFrz                                                  : 1;
    UINT64 CtrFrz                                                  : 1;
    UINT64 Asci                                                    : 1;
    UINT64 OvfUncore                                               : 1;
    UINT64 OvfBuf                                                  : 1;
    UINT64 CondChgd                                                : 1;
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_REGISTER;

/**
 * @brief Global Performance Counter Control. Counter increments while the result of ANDing the respective enable bit in
 *        this MSR with the corresponding OS or USR bits in the general-purpose or fixed counter control MSR is true. <b>(R/W)</b>
 */
#define IA32_PERF_GLOBAL_CTRL                                        0x0000038F

typedef struct
{
  UINT32 EnPmcn;
  UINT32 EnFixedCtrn;
} IA32_PERF_GLOBAL_CTRL_REGISTER;

/**
 * @brief Global Performance Counter Overflow Reset Control. <b>(R/W)</b>
 */
#define IA32_PERF_GLOBAL_STATUS_RESET                                0x00000390

typedef union
{
  struct
  {
    UINT64 ClearOvfPmcn                                            : 32;
    UINT64 ClearOvfFixedCtrn                                       : 3;
    UINT64 Reserved1                                               : 20;
    UINT64 ClearTraceTopaPmi                                       : 1;
    UINT64 Reserved2                                               : 2;
    UINT64 ClearLbrFrz                                             : 1;
    UINT64 ClearCtrFrz                                             : 1;
    UINT64 ClearAsci                                               : 1;
    UINT64 ClearOvfUncore                                          : 1;
    UINT64 ClearOvfBuf                                             : 1;
    UINT64 ClearCondChgd                                           : 1;
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_RESET_REGISTER;

/**
 * @brief Global Performance Counter Overflow Set Control. <b>(R/W)</b>
 */
#define IA32_PERF_GLOBAL_STATUS_SET                                  0x00000391

typedef union
{
  struct
  {
    UINT64 OvfPmcn                                                 : 32;
    UINT64 OvfFixedCtrn                                            : 3;
    UINT64 Reserved1                                               : 20;
    UINT64 TraceTopaPmi                                            : 1;
    UINT64 Reserved2                                               : 2;
    UINT64 LbrFrz                                                  : 1;
    UINT64 CtrFrz                                                  : 1;
    UINT64 Asci                                                    : 1;
    UINT64 OvfUncore                                               : 1;
    UINT64 OvfBuf                                                  : 1;
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_STATUS_SET_REGISTER;

/**
 * @brief Indicator that core perfmon interface is in use. <b>(RO)</b>
 */
#define IA32_PERF_GLOBAL_INUSE                                       0x00000392

typedef union
{
  struct
  {
    UINT64 Ia32PerfevtselnInUse                                    : 32;
    UINT64 Ia32FixedCtrnInUse                                      : 3;
    UINT64 Reserved1                                               : 28;
    UINT64 PmiInUse                                                : 1;
  };

  UINT64 Flags;
} IA32_PERF_GLOBAL_INUSE_REGISTER;

/**
 * @brief PEBS Control. <b>(R/W)</b>
 */
#define IA32_PEBS_ENABLE                                             0x000003F1

typedef union
{
  struct
  {
    UINT64 EnablePebs                                              : 1;
    UINT64 Reservedormodelspecific1                                : 3;
    UINT64 Reserved1                                               : 28;
    UINT64 Reservedormodelspecific2                                : 4;
  };

  UINT64 Flags;
} IA32_PEBS_ENABLE_REGISTER;

/**
 * @defgroup IA32_MC_CTL \
 *           IA32_MC(i)_CTL
 *
 * IA32_MC(0-28)_CTL.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_CTL                                                 0x00000400
#define IA32_MC1_CTL                                                 0x00000404
#define IA32_MC2_CTL                                                 0x00000408
#define IA32_MC3_CTL                                                 0x0000040C
#define IA32_MC4_CTL                                                 0x00000410
#define IA32_MC5_CTL                                                 0x00000414
#define IA32_MC6_CTL                                                 0x00000418
#define IA32_MC7_CTL                                                 0x0000041C
#define IA32_MC8_CTL                                                 0x00000420
#define IA32_MC9_CTL                                                 0x00000424
#define IA32_MC10_CTL                                                0x00000428
#define IA32_MC11_CTL                                                0x0000042C
#define IA32_MC12_CTL                                                0x00000430
#define IA32_MC13_CTL                                                0x00000434
#define IA32_MC14_CTL                                                0x00000438
#define IA32_MC15_CTL                                                0x0000043C
#define IA32_MC16_CTL                                                0x00000440
#define IA32_MC17_CTL                                                0x00000444
#define IA32_MC18_CTL                                                0x00000448
#define IA32_MC19_CTL                                                0x0000044C
#define IA32_MC20_CTL                                                0x00000450
#define IA32_MC21_CTL                                                0x00000454
#define IA32_MC22_CTL                                                0x00000458
#define IA32_MC23_CTL                                                0x0000045C
#define IA32_MC24_CTL                                                0x00000460
#define IA32_MC25_CTL                                                0x00000464
#define IA32_MC26_CTL                                                0x00000468
#define IA32_MC27_CTL                                                0x0000046C
#define IA32_MC28_CTL                                                0x00000470
/**
 * @}
 */

/**
 * @defgroup IA32_MC_STATUS \
 *           IA32_MC(i)_STATUS
 *
 * IA32_MC(0-28)_STATUS.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_STATUS                                              0x00000401
#define IA32_MC1_STATUS                                              0x00000405
#define IA32_MC2_STATUS                                              0x00000409
#define IA32_MC3_STATUS                                              0x0000040D
#define IA32_MC4_STATUS                                              0x00000411
#define IA32_MC5_STATUS                                              0x00000415
#define IA32_MC6_STATUS                                              0x00000419
#define IA32_MC7_STATUS                                              0x0000041D
#define IA32_MC8_STATUS                                              0x00000421
#define IA32_MC9_STATUS                                              0x00000425
#define IA32_MC10_STATUS                                             0x00000429
#define IA32_MC11_STATUS                                             0x0000042D
#define IA32_MC12_STATUS                                             0x00000431
#define IA32_MC13_STATUS                                             0x00000435
#define IA32_MC14_STATUS                                             0x00000439
#define IA32_MC15_STATUS                                             0x0000043D
#define IA32_MC16_STATUS                                             0x00000441
#define IA32_MC17_STATUS                                             0x00000445
#define IA32_MC18_STATUS                                             0x00000449
#define IA32_MC19_STATUS                                             0x0000044D
#define IA32_MC20_STATUS                                             0x00000451
#define IA32_MC21_STATUS                                             0x00000455
#define IA32_MC22_STATUS                                             0x00000459
#define IA32_MC23_STATUS                                             0x0000045D
#define IA32_MC24_STATUS                                             0x00000461
#define IA32_MC25_STATUS                                             0x00000465
#define IA32_MC26_STATUS                                             0x00000469
#define IA32_MC27_STATUS                                             0x0000046D
#define IA32_MC28_STATUS                                             0x00000471
/**
 * @}
 */

/**
 * @defgroup IA32_MC_ADDR \
 *           IA32_MC(i)_ADDR
 *
 * IA32_MC(0-28)_ADDR.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_ADDR                                                0x00000402
#define IA32_MC1_ADDR                                                0x00000406
#define IA32_MC2_ADDR                                                0x0000040A
#define IA32_MC3_ADDR                                                0x0000040E
#define IA32_MC4_ADDR                                                0x00000412
#define IA32_MC5_ADDR                                                0x00000416
#define IA32_MC6_ADDR                                                0x0000041A
#define IA32_MC7_ADDR                                                0x0000041E
#define IA32_MC8_ADDR                                                0x00000422
#define IA32_MC9_ADDR                                                0x00000426
#define IA32_MC10_ADDR                                               0x0000042A
#define IA32_MC11_ADDR                                               0x0000042E
#define IA32_MC12_ADDR                                               0x00000432
#define IA32_MC13_ADDR                                               0x00000436
#define IA32_MC14_ADDR                                               0x0000043A
#define IA32_MC15_ADDR                                               0x0000043E
#define IA32_MC16_ADDR                                               0x00000442
#define IA32_MC17_ADDR                                               0x00000446
#define IA32_MC18_ADDR                                               0x0000044A
#define IA32_MC19_ADDR                                               0x0000044E
#define IA32_MC20_ADDR                                               0x00000452
#define IA32_MC21_ADDR                                               0x00000456
#define IA32_MC22_ADDR                                               0x0000045A
#define IA32_MC23_ADDR                                               0x0000045E
#define IA32_MC24_ADDR                                               0x00000462
#define IA32_MC25_ADDR                                               0x00000466
#define IA32_MC26_ADDR                                               0x0000046A
#define IA32_MC27_ADDR                                               0x0000046E
#define IA32_MC28_ADDR                                               0x00000472
/**
 * @}
 */

/**
 * @defgroup IA32_MC_MISC \
 *           IA32_MC(i)_MISC
 *
 * IA32_MC(0-28)_MISC.
 *
 * @remarks If IA32_MCG_CAP.CNT > n
 * @{
 */
#define IA32_MC0_MISC                                                0x00000403
#define IA32_MC1_MISC                                                0x00000407
#define IA32_MC2_MISC                                                0x0000040B
#define IA32_MC3_MISC                                                0x0000040F
#define IA32_MC4_MISC                                                0x00000413
#define IA32_MC5_MISC                                                0x00000417
#define IA32_MC6_MISC                                                0x0000041B
#define IA32_MC7_MISC                                                0x0000041F
#define IA32_MC8_MISC                                                0x00000423
#define IA32_MC9_MISC                                                0x00000427
#define IA32_MC10_MISC                                               0x0000042B
#define IA32_MC11_MISC                                               0x0000042F
#define IA32_MC12_MISC                                               0x00000433
#define IA32_MC13_MISC                                               0x00000437
#define IA32_MC14_MISC                                               0x0000043B
#define IA32_MC15_MISC                                               0x0000043F
#define IA32_MC16_MISC                                               0x00000443
#define IA32_MC17_MISC                                               0x00000447
#define IA32_MC18_MISC                                               0x0000044B
#define IA32_MC19_MISC                                               0x0000044F
#define IA32_MC20_MISC                                               0x00000453
#define IA32_MC21_MISC                                               0x00000457
#define IA32_MC22_MISC                                               0x0000045B
#define IA32_MC23_MISC                                               0x0000045F
#define IA32_MC24_MISC                                               0x00000463
#define IA32_MC25_MISC                                               0x00000467
#define IA32_MC26_MISC                                               0x0000046B
#define IA32_MC27_MISC                                               0x0000046F
#define IA32_MC28_MISC                                               0x00000473
/**
 * @}
 */

/**
 * @brief Reporting Register of Basic VMX Capabilities. <b>(R/O)</b>
 */
#define IA32_VMX_BASIC                                               0x00000480

typedef union
{
  struct
  {
    UINT64 VmcsRevisionId                                          : 31;
    UINT64 MustBeZero                                              : 1;
    UINT64 VmcsSizeInBytes                                         : 13;
    UINT64 Reserved1                                               : 3;
    UINT64 VmcsPhysicalAddressWidth                                : 1;
    UINT64 DualMonitorSupport                                      : 1;
    UINT64 MemoryType                                              : 4;
    UINT64 InsOutsReporting                                        : 1;
    UINT64 VmxControls                                             : 1;
  };

  UINT64 Flags;
} IA32_VMX_BASIC_REGISTER;

/**
 * @brief Capability Reporting Register of Pin-Based VM-Execution Controls. <b>(R/O)</b>
 */
#define IA32_VMX_PINBASED_CTLS                                       0x00000481

typedef union
{
  struct
  {
    UINT64 ExternalInterruptExiting                                : 1;
    UINT64 Reserved1                                               : 2;
    UINT64 NmiExiting                                              : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 VirtualNmi                                              : 1;
    UINT64 ActivateVmxPreemptionTimer                              : 1;
    UINT64 ProcessPostedInterrupts                                 : 1;
  };

  UINT64 Flags;
} IA32_VMX_PINBASED_CTLS_REGISTER;

/**
 * @brief Capability Reporting Register of Primary Processor-Based VM-Execution Controls. <b>(R/O)</b>
 */
#define IA32_VMX_PROCBASED_CTLS                                      0x00000482

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;
    UINT64 InterruptWindowExiting                                  : 1;
    UINT64 UseTscOffsetting                                        : 1;
    UINT64 Reserved2                                               : 3;
    UINT64 HltExiting                                              : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 InvlpgExiting                                           : 1;
    UINT64 MwaitExiting                                            : 1;
    UINT64 RdpmcExiting                                            : 1;
    UINT64 RdtscExiting                                            : 1;
    UINT64 Reserved4                                               : 2;
    UINT64 Cr3LoadExiting                                          : 1;
    UINT64 Cr3StoreExiting                                         : 1;
    UINT64 Reserved5                                               : 2;
    UINT64 Cr8LoadExiting                                          : 1;
    UINT64 Cr8StoreExiting                                         : 1;
    UINT64 UseTprShadow                                            : 1;
    UINT64 NmiWindowExiting                                        : 1;
    UINT64 MovDrExiting                                            : 1;
    UINT64 UnconditionalIoExiting                                  : 1;
    UINT64 UseIoBitmaps                                            : 1;
    UINT64 Reserved6                                               : 1;
    UINT64 MonitorTrapFlag                                         : 1;
    UINT64 UseMsrBitmaps                                           : 1;
    UINT64 MonitorExiting                                          : 1;
    UINT64 PauseExiting                                            : 1;
    UINT64 ActivateSecondaryControls                               : 1;
  };

  UINT64 Flags;
} IA32_VMX_PROCBASED_CTLS_REGISTER;

/**
 * @brief Capability Reporting Register of VM-Exit Controls. <b>(R/O)</b>
 */
#define IA32_VMX_EXIT_CTLS                                           0x00000483

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;
    UINT64 SaveDebugControls                                       : 1;
    UINT64 Reserved2                                               : 6;
    UINT64 HostAddressSpaceSize                                    : 1;
    UINT64 Reserved3                                               : 2;
    UINT64 LoadIa32PerfGlobalCtrl                                  : 1;
    UINT64 Reserved4                                               : 2;
    UINT64 AcknowledgeInterruptOnExit                              : 1;
    UINT64 Reserved5                                               : 2;
    UINT64 SaveIa32Pat                                             : 1;
    UINT64 LoadIa32Pat                                             : 1;
    UINT64 SaveIa32Efer                                            : 1;
    UINT64 LoadIa32Efer                                            : 1;
    UINT64 SaveVmxPreemptionTimerValue                             : 1;
    UINT64 ClearIa32Bndcfgs                                        : 1;
    UINT64 ConcealVmxFromPt                                        : 1;
  };

  UINT64 Flags;
} IA32_VMX_EXIT_CTLS_REGISTER;

/**
 * @brief Capability Reporting Register of VM-Entry Controls. <b>(R/O)</b>
 */
#define IA32_VMX_ENTRY_CTLS                                          0x00000484

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 2;
    UINT64 LoadDebugControls                                       : 1;
    UINT64 Reserved2                                               : 6;
    UINT64 Ia32EModeGuest                                          : 1;
    UINT64 EntryToSmm                                              : 1;
    UINT64 DeactivateDualMonitorTreatment                          : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 LoadIa32PerfGlobalCtrl                                  : 1;
    UINT64 LoadIa32Pat                                             : 1;
    UINT64 LoadIa32Efer                                            : 1;
    UINT64 LoadIa32Bndcfgs                                         : 1;
    UINT64 ConcealVmxFromPt                                        : 1;
  };

  UINT64 Flags;
} IA32_VMX_ENTRY_CTLS_REGISTER;

/**
 * @brief Reporting Register of Miscellaneous VMX Capabilities. <b>(R/O)</b>
 */
#define IA32_VMX_MISC                                                0x00000485

typedef union
{
  struct
  {
    UINT64 PreemptionTimerTscRelationship                          : 5;
    UINT64 StoreEferLmaOnVmexit                                    : 1;
    UINT64 ActivityStates                                          : 3;
    UINT64 Reserved1                                               : 5;
    UINT64 IntelPtAvailableInVmx                                   : 1;
    UINT64 RdmsrCanReadIa32SmbaseMsrInSmm                          : 1;
    UINT64 Cr3TargetCount                                          : 9;
    UINT64 MaxNumberOfMsr                                          : 3;
    UINT64 SmmMonitorCtlB2                                         : 1;
    UINT64 VmwriteVmexitInfo                                       : 1;
    UINT64 ZeroLengthInstructionVmentryInjection                   : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 MsegId                                                  : 32;
  };

  UINT64 Flags;
} IA32_VMX_MISC_REGISTER;

/**
 * @brief Capability Reporting Register of CR0 Bits Fixed to 0. <b>(R/O)</b>
 */
#define IA32_VMX_CR0_FIXED0                                          0x00000486

/**
 * @brief Capability Reporting Register of CR0 Bits Fixed to 1. <b>(R/O)</b>
 */
#define IA32_VMX_CR0_FIXED1                                          0x00000487

/**
 * @brief Capability Reporting Register of CR4 Bits Fixed to 0. <b>(R/O)</b>
 */
#define IA32_VMX_CR4_FIXED0                                          0x00000488

/**
 * @brief Capability Reporting Register of CR4 Bits Fixed to 1. <b>(R/O)</b>
 */
#define IA32_VMX_CR4_FIXED1                                          0x00000489

/**
 * @brief Capability Reporting Register of VMCS Field Enumeration. <b>(R/O)</b>
 */
#define IA32_VMX_VMCS_ENUM                                           0x0000048A

typedef union
{
  struct
  {
    UINT64 AccessType                                              : 1;
    UINT64 HighestIndexValue                                       : 9;
    UINT64 FieldType                                               : 2;
    UINT64 Reserved1                                               : 1;
    UINT64 FieldWidth                                              : 2;
  };

  UINT64 Flags;
} IA32_VMX_VMCS_ENUM_REGISTER;

/**
 * @brief Capability Reporting Register of Secondary Processor-Based VM-Execution Controls. <b>(R/O)</b>
 */
#define IA32_VMX_PROCBASED_CTLS2                                     0x0000048B

typedef union
{
  struct
  {
    UINT64 VirtualizeApicAccesses                                  : 1;
    UINT64 EnableEpt                                               : 1;
    UINT64 DescriptorTableExiting                                  : 1;
    UINT64 EnableRdtscp                                            : 1;
    UINT64 VirtualizeX2ApicMode                                    : 1;
    UINT64 EnableVpid                                              : 1;
    UINT64 WbinvdExiting                                           : 1;
    UINT64 UnrestrictedGuest                                       : 1;
    UINT64 ApicRegisterVirtualization                              : 1;
    UINT64 VirtualInterruptDelivery                                : 1;
    UINT64 PauseLoopExiting                                        : 1;
    UINT64 RdrandExiting                                           : 1;
    UINT64 EnableInvpcid                                           : 1;
    UINT64 EnableVmFunctions                                       : 1;
    UINT64 VmcsShadowing                                           : 1;
    UINT64 EnableEnclsExiting                                      : 1;
    UINT64 RdseedExiting                                           : 1;
    UINT64 EnablePml                                               : 1;
    UINT64 EptViolation                                            : 1;
    UINT64 ConcealVmxFromPt                                        : 1;
    UINT64 EnableXsaves                                            : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 ModeBasedExecuteControlForEpt                           : 1;
    UINT64 Reserved2                                               : 2;
    UINT64 UseTscScaling                                           : 1;
  };

  UINT64 Flags;
} IA32_VMX_PROCBASED_CTLS2_REGISTER;

/**
 * @brief Capability Reporting Register of EPT and VPID. <b>(R/O)</b>
 */
#define IA32_VMX_EPT_VPID_CAP                                        0x0000048C

typedef union
{
  struct
  {
    UINT64 ExecuteOnlyPages                                        : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 PageWalkLength4                                         : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 MemoryTypeUncacheable                                   : 1;
    UINT64 Reserved3                                               : 5;
    UINT64 MemoryTypeWriteBack                                     : 1;
    UINT64 Reserved4                                               : 1;
    UINT64 Pde2MbPages                                             : 1;
    UINT64 Pdpte1GbPages                                           : 1;
    UINT64 Reserved5                                               : 2;
    UINT64 Invept                                                  : 1;
    UINT64 EptAccessedAndDirtyFlags                                : 1;
    UINT64 AdvancedVmexitEptViolationsInformation                  : 1;
    UINT64 Reserved6                                               : 2;
    UINT64 InveptSingleContext                                     : 1;
    UINT64 InveptAllContexts                                       : 1;
    UINT64 Reserved7                                               : 5;
    UINT64 Invvpid                                                 : 1;
    UINT64 Reserved8                                               : 7;
    UINT64 InvvpidIndividualAddress                                : 1;
    UINT64 InvvpidSingleContext                                    : 1;
    UINT64 InvvpidAllContexts                                      : 1;
    UINT64 InvvpidSingleContextRetainGlobals                       : 1;
  };

  UINT64 Flags;
} IA32_VMX_EPT_VPID_CAP_REGISTER;

/**
 * @defgroup IA32_VMX_TRUE_CTLS \
 *           IA32_VMX_TRUE_(x)_CTLS
 *
 * Capability Reporting Register of Pin-Based VM-Execution Flex Controls, Primary Processor-Based VM-Execution Flex
 * Controls, VM-Exit Flex Controls and VM-Entry Flex Controls.
 *
 * @remarks If ( CPUID.01H:ECX.[5] = 1 && IA32_VMX_BASIC[55] )
 * @see Vol3D[A.3.1(Pin-Based VM-Execution Controls)]
 * @see Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)]
 * @see Vol3D[A.4(VM-EXIT CONTROLS)]
 * @see Vol3D[A.5(VM-ENTRY CONTROLS)]
 * @see ['Vol3D[A.3.1(Pin-Based VMExecution Controls)]', 'Vol3D[A.3.2(Primary Processor-Based VM-Execution Controls)]', 'Vol3D[A.4(VM-Exit Controls)]', 'Vol3D[A.5(VM-Entry Controls)]'] (reference)
 * @{
 */
#define IA32_VMX_TRUE_PINBASED_CTLS                                  0x0000048D
#define IA32_VMX_TRUE_PROCBASED_CTLS                                 0x0000048E
#define IA32_VMX_TRUE_EXIT_CTLS                                      0x0000048F
#define IA32_VMX_TRUE_ENTRY_CTLS                                     0x00000490
typedef struct
{
  UINT32 Allowed0Settings;
  UINT32 Allowed1Settings;
} IA32_VMX_TRUE_CTLS_REGISTER;

/**
 * @}
 */

/**
 * @brief Capability Reporting Register of VMFunction Controls. <b>(R/O)</b>
 */
#define IA32_VMX_VMFUNC                                              0x00000491

typedef union
{
  struct
  {
    UINT64 EptpSwitching                                           : 1;
  };

  UINT64 Flags;
} IA32_VMX_VMFUNC_REGISTER;

/**
 * @defgroup IA32_A_PMC \
 *           IA32_A_PMC(n)
 *
 * Full Width Writable IA32_PMC(n) Alias.
 *
 * @remarks (If CPUID.0AH: EAX[15:8] > 0) && IA32_PERF_CAPABILITIES[13] = 1
 * @{
 */
#define IA32_A_PMC0                                                  0x000004C1
#define IA32_A_PMC1                                                  0x000004C2
#define IA32_A_PMC2                                                  0x000004C3
#define IA32_A_PMC3                                                  0x000004C4
#define IA32_A_PMC4                                                  0x000004C5
#define IA32_A_PMC5                                                  0x000004C6
#define IA32_A_PMC6                                                  0x000004C7
#define IA32_A_PMC7                                                  0x000004C8
/**
 * @}
 */

/**
 * @brief Allows software to signal some MCEs to only a single logical processor in the system. <b>(R/W)</b>
 */
#define IA32_MCG_EXT_CTL                                             0x000004D0

typedef union
{
  struct
  {
    UINT64 LmceEn                                                  : 1;
  };

  UINT64 Flags;
} IA32_MCG_EXT_CTL_REGISTER;

/**
 * @brief Intel SGX only allows launching ACMs with an Intel SGX SVN that is at the same level or higher than the expected
 *        Intel SGX SVN. The expected Intel SGX SVN is specified by BIOS and locked down by the processor on the first successful
 *        execution of an Intel SGX instruction that doesn't return an error code. Intel SGX provides interfaces for system
 *        software to discover whether a non faulting Intel SGX instruction has been executed, and evaluate the suitability of the
 *        Intel SGX SVN value of any ACM that is expected to be launched by the OS or the VMM. <b>(RO)</b>
 */
#define IA32_SGX_SVN_STATUS                                          0x00000500

typedef union
{
  struct
  {
    UINT64 Lock                                                    : 1;
    UINT64 Reserved1                                               : 15;
    UINT64 SgxSvnSinit                                             : 8;
  };

  UINT64 Flags;
} IA32_SGX_SVN_STATUS_REGISTER;

/**
 * @brief Trace Output Base Register. <b>(R/W)</b>
 */
#define IA32_RTIT_OUTPUT_BASE                                        0x00000560

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 7;
    UINT64 BasePhysicalAddress                                     : 41;
  };

  UINT64 Flags;
} IA32_RTIT_OUTPUT_BASE_REGISTER;

/**
 * @brief Trace Output Mask Pointers Register. <b>(R/W)</b>
 */
#define IA32_RTIT_OUTPUT_MASK_PTRS                                   0x00000561

typedef union
{
  struct
  {
    UINT64 LowerMask                                               : 7;
    UINT64 MaskOrTableOffset                                       : 25;
    UINT64 OutputOffset                                            : 32;
  };

  UINT64 Flags;
} IA32_RTIT_OUTPUT_MASK_PTRS_REGISTER;

/**
 * @brief Trace Control Register. <b>(R/W)</b>
 */
#define IA32_RTIT_CTL                                                0x00000570

typedef union
{
  struct
  {
    UINT64 TraceEnabled                                            : 1;
    UINT64 CycEnabled                                              : 1;
    UINT64 Os                                                      : 1;
    UINT64 User                                                    : 1;
    UINT64 PowerEventTraceEnabled                                  : 1;
    UINT64 FupOnPtw                                                : 1;
    UINT64 FabricEnabled                                           : 1;
    UINT64 Cr3Filter                                               : 1;
    UINT64 Topa                                                    : 1;
    UINT64 MtcEnabled                                              : 1;
    UINT64 TscEnabled                                              : 1;
    UINT64 RetCompressionDisabled                                  : 1;
    UINT64 PtwEnabled                                              : 1;
    UINT64 BranchEnabled                                           : 1;
    UINT64 MtcFrequency                                            : 4;
    UINT64 Reserved1                                               : 1;
    UINT64 CycThreshold                                            : 4;
    UINT64 Reserved2                                               : 1;
    UINT64 PsbFrequency                                            : 4;
    UINT64 Reserved3                                               : 4;
    UINT64 Addr0Cfg                                                : 4;
    UINT64 Addr1Cfg                                                : 4;
    UINT64 Addr2Cfg                                                : 4;
    UINT64 Addr3Cfg                                                : 4;
    UINT64 Reserved4                                               : 8;
    UINT64 InjectPsbPmiOnEnable                                    : 1;
  };

  UINT64 Flags;
} IA32_RTIT_CTL_REGISTER;

/**
 * @brief Tracing Status Register. <b>(R/W)</b>
 */
#define IA32_RTIT_STATUS                                             0x00000571

typedef union
{
  struct
  {
    UINT64 FilterEnabled                                           : 1;
    UINT64 ContextEnabled                                          : 1;
    UINT64 TriggerEnabled                                          : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 Error                                                   : 1;
    UINT64 Stopped                                                 : 1;
    UINT64 PendPsb                                                 : 1;
    UINT64 PendTopaPmi                                             : 1;
    UINT64 Reserved2                                               : 24;
    UINT64 PacketByteCount                                         : 17;
  };

  UINT64 Flags;
} IA32_RTIT_STATUS_REGISTER;

/**
 * @brief The IA32_RTIT_CR3_MATCH register is compared against CR3 when IA32_RTIT_CTL.CR3Filter is 1. Bits 63:5 hold the
 *        CR3 address value to match, bits 4:0 are reserved to 0. <b>(R/W)</b>
 */
#define IA32_RTIT_CR3_MATCH                                          0x00000572

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 5;
    UINT64 Cr3ValueToMatch                                         : 59;
  };

  UINT64 Flags;
} IA32_RTIT_CR3_MATCH_REGISTER;

/**
 * @defgroup IA32_RTIT_ADDR \
 *           IA32_RTIT_ADDR(x)
 *
 * The role of the IA32_RTIT_ADDRn_A/B register pairs, for each n, is determined by the corresponding ADDRn_CFG fields in
 * IA32_RTIT_CTL. The number of these register pairs is enumerated by CPUID.(EAX=14H, ECX=1):EAX.RANGECNT[2:0].
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @see Vol3C[35.2.7.2(IA32_RTIT_CTL MSR)]
 * @see Vol3C[35.2.7.5(IA32_RTIT_ADDRn_A and IA32_RTIT_ADDRn_B MSRs)] (reference)
 * @{
 */
/**
 * @defgroup IA32_RTIT_ADDR_A \
 *           IA32_RTIT_ADDR(n)_A
 *
 * Region n Start Address.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @{
 */
#define IA32_RTIT_ADDR0_A                                            0x00000580
#define IA32_RTIT_ADDR1_A                                            0x00000582
#define IA32_RTIT_ADDR2_A                                            0x00000584
#define IA32_RTIT_ADDR3_A                                            0x00000586
/**
 * @}
 */

/**
 * @defgroup IA32_RTIT_ADDR_B \
 *           IA32_RTIT_ADDR(n)_B
 *
 * Region n End Address.
 *
 * @remarks If (CPUID.(EAX=07H, ECX=1):EAX[2:0] > n)
 * @{
 */
#define IA32_RTIT_ADDR0_B                                            0x00000581
#define IA32_RTIT_ADDR1_B                                            0x00000583
#define IA32_RTIT_ADDR2_B                                            0x00000585
#define IA32_RTIT_ADDR3_B                                            0x00000587
/**
 * @}
 */

typedef union
{
  struct
  {
    UINT64 VirtualAddress                                          : 48;
    UINT64 SignExtVa                                               : 16;
  };

  UINT64 Flags;
} IA32_RTIT_ADDR_REGISTER;

/**
 * @}
 */

/**
 * @brief DS Save Area. Points to the linear address of the first byte of the DS buffer management area, which is used to
 *        manage the BTS and PEBS buffers.
 *        Returns:
 *        - [63:0] The linear address of the first byte of the DS buffer management area, if IA-32e mode is active.
 *        - [31:0] The linear address of the first byte of the DS buffer management area, if not in IA-32e mode.
 *        - [63:32] Reserved if not in IA-32e mode. <b>(R/W)</b>
 */
#define IA32_DS_AREA                                                 0x00000600

/**
 * @brief TSC Target of Local APIC's TSC Deadline Mode. <b>(R/W)</b>
 */
#define IA32_TSC_DEADLINE                                            0x000006E0

/**
 * @brief Enable/disable HWP. <b>(R/W)</b>
 */
#define IA32_PM_ENABLE                                               0x00000770

typedef union
{
  struct
  {
    UINT64 HwpEnable                                               : 1;
  };

  UINT64 Flags;
} IA32_PM_ENABLE_REGISTER;

/**
 * @brief HWP Performance Range Enumeration. <b>(RO)</b>
 */
#define IA32_HWP_CAPABILITIES                                        0x00000771

typedef union
{
  struct
  {
    UINT64 HighestPerformance                                      : 8;
    UINT64 GuaranteedPerformance                                   : 8;
    UINT64 MostEfficientPerformance                                : 8;
    UINT64 LowestPerformance                                       : 8;
  };

  UINT64 Flags;
} IA32_HWP_CAPABILITIES_REGISTER;

/**
 * @brief Power Management Control Hints for All Logical Processors in a Package. <b>(R/W)</b>
 */
#define IA32_HWP_REQUEST_PKG                                         0x00000772

typedef union
{
  struct
  {
    UINT64 MinimumPerformance                                      : 8;
    UINT64 MaximumPerformance                                      : 8;
    UINT64 DesiredPerformance                                      : 8;
    UINT64 EnergyPerformancePreference                             : 8;
    UINT64 ActivityWindow                                          : 10;
  };

  UINT64 Flags;
} IA32_HWP_REQUEST_PKG_REGISTER;

/**
 * @brief Control HWP Native Interrupts. <b>(R/W)</b>
 */
#define IA32_HWP_INTERRUPT                                           0x00000773

typedef union
{
  struct
  {
    UINT64 EnGuaranteedPerformanceChange                           : 1;
    UINT64 EnExcursionMinimum                                      : 1;
  };

  UINT64 Flags;
} IA32_HWP_INTERRUPT_REGISTER;

/**
 * @brief Power Management Control Hints to a Logical Processor. <b>(R/W)</b>
 */
#define IA32_HWP_REQUEST                                             0x00000774

typedef union
{
  struct
  {
    UINT64 MinimumPerformance                                      : 8;
    UINT64 MaximumPerformance                                      : 8;
    UINT64 DesiredPerformance                                      : 8;
    UINT64 EnergyPerformancePreference                             : 8;
    UINT64 ActivityWindow                                          : 10;
    UINT64 PackageControl                                          : 1;
  };

  UINT64 Flags;
} IA32_HWP_REQUEST_REGISTER;

/**
 * @brief Log bits indicating changes to Guaranteed & excursions to Minimum. <b>(R/W)</b>
 */
#define IA32_HWP_STATUS                                              0x00000777

typedef union
{
  struct
  {
    UINT64 GuaranteedPerformanceChange                             : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 ExcursionToMinimum                                      : 1;
  };

  UINT64 Flags;
} IA32_HWP_STATUS_REGISTER;

/**
 * @brief x2APIC ID Register. <b>(R/O)</b>
 */
#define IA32_X2APIC_APICID                                           0x00000802

/**
 * @brief x2APIC Version Register. <b>(R/O)</b>
 */
#define IA32_X2APIC_VERSION                                          0x00000803

/**
 * @brief x2APIC Task Priority Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_TPR                                              0x00000808

/**
 * @brief x2APIC Processor Priority Register. <b>(R/O)</b>
 */
#define IA32_X2APIC_PPR                                              0x0000080A

/**
 * @brief x2APIC EOI Register. <b>(W/O)</b>
 */
#define IA32_X2APIC_EOI                                              0x0000080B

/**
 * @brief x2APIC Logical Destination Register. <b>(R/O)</b>
 */
#define IA32_X2APIC_LDR                                              0x0000080D

/**
 * @brief x2APIC Spurious Interrupt Vector Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_SIVR                                             0x0000080F

/**
 * @defgroup IA32_X2APIC_ISR \
 *           IA32_X2APIC_ISR(n)
 *
 * x2APIC In-Service Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_ISR0                                             0x00000810
#define IA32_X2APIC_ISR1                                             0x00000811
#define IA32_X2APIC_ISR2                                             0x00000812
#define IA32_X2APIC_ISR3                                             0x00000813
#define IA32_X2APIC_ISR4                                             0x00000814
#define IA32_X2APIC_ISR5                                             0x00000815
#define IA32_X2APIC_ISR6                                             0x00000816
#define IA32_X2APIC_ISR7                                             0x00000817
/**
 * @}
 */

/**
 * @defgroup IA32_X2APIC_TMR \
 *           IA32_X2APIC_TMR(n)
 *
 * x2APIC Trigger Mode Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_TMR0                                             0x00000818
#define IA32_X2APIC_TMR1                                             0x00000819
#define IA32_X2APIC_TMR2                                             0x0000081A
#define IA32_X2APIC_TMR3                                             0x0000081B
#define IA32_X2APIC_TMR4                                             0x0000081C
#define IA32_X2APIC_TMR5                                             0x0000081D
#define IA32_X2APIC_TMR6                                             0x0000081E
#define IA32_X2APIC_TMR7                                             0x0000081F
/**
 * @}
 */

/**
 * @defgroup IA32_X2APIC_IRR \
 *           IA32_X2APIC_IRR(n)
 *
 * x2APIC Interrupt Request Register Bits (n * 32 + 31):(n * 32).
 *
 * @remarks If CPUID.01H:ECX.[21] = 1 && IA32_APIC_BASE.[10] = 1
 * @{
 */
#define IA32_X2APIC_IRR0                                             0x00000820
#define IA32_X2APIC_IRR1                                             0x00000821
#define IA32_X2APIC_IRR2                                             0x00000822
#define IA32_X2APIC_IRR3                                             0x00000823
#define IA32_X2APIC_IRR4                                             0x00000824
#define IA32_X2APIC_IRR5                                             0x00000825
#define IA32_X2APIC_IRR6                                             0x00000826
#define IA32_X2APIC_IRR7                                             0x00000827
/**
 * @}
 */

/**
 * @brief x2APIC Error Status Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_ESR                                              0x00000828

/**
 * @brief x2APIC LVT Corrected Machine Check Interrupt Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_CMCI                                         0x0000082F

/**
 * @brief x2APIC Interrupt Command Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_ICR                                              0x00000830

/**
 * @brief x2APIC LVT Timer Interrupt Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_TIMER                                        0x00000832

/**
 * @brief x2APIC LVT Thermal Sensor Interrupt Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_THERMAL                                      0x00000833

/**
 * @brief x2APIC LVT Performance Monitor Interrupt Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_PMI                                          0x00000834

/**
 * @brief x2APIC LVT LINT0 Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_LINT0                                        0x00000835

/**
 * @brief x2APIC LVT LINT1 Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_LINT1                                        0x00000836

/**
 * @brief x2APIC LVT Error Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_LVT_ERROR                                        0x00000837

/**
 * @brief x2APIC Initial Count Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_INIT_COUNT                                       0x00000838

/**
 * @brief x2APIC Current Count Register. <b>(R/O)</b>
 */
#define IA32_X2APIC_CUR_COUNT                                        0x00000839

/**
 * @brief x2APIC Divide Configuration Register. <b>(R/W)</b>
 */
#define IA32_X2APIC_DIV_CONF                                         0x0000083E

/**
 * @brief x2APIC Self IPI Register. <b>(W/O)</b>
 */
#define IA32_X2APIC_SELF_IPI                                         0x0000083F

/**
 * @brief Silicon Debug Feature Control. <b>(R/W)</b>
 */
#define IA32_DEBUG_INTERFACE                                         0x00000C80

typedef union
{
  struct
  {
    UINT64 Enable                                                  : 1;
    UINT64 Reserved1                                               : 29;
    UINT64 Lock                                                    : 1;
    UINT64 DebugOccurred                                           : 1;
  };

  UINT64 Flags;
} IA32_DEBUG_INTERFACE_REGISTER;

/**
 * @brief L3 QOS Configuration. <b>(R/W)</b>
 */
#define IA32_L3_QOS_CFG                                              0x00000C81

typedef union
{
  struct
  {
    UINT64 Enable                                                  : 1;
  };

  UINT64 Flags;
} IA32_L3_QOS_CFG_REGISTER;

/**
 * @brief L2 QOS Configuration. <b>(R/W)</b>
 */
#define IA32_L2_QOS_CFG                                              0x00000C82

typedef union
{
  struct
  {
    UINT64 Enable                                                  : 1;
  };

  UINT64 Flags;
} IA32_L2_QOS_CFG_REGISTER;

/**
 * @brief Monitoring Event Select Register. <b>(R/W)</b>
 */
#define IA32_QM_EVTSEL                                               0x00000C8D

typedef union
{
  struct
  {
    UINT64 EventId                                                 : 8;
    UINT64 Reserved1                                               : 24;
    UINT64 ResourceMonitoringId                                    : 32;
  };

  UINT64 Flags;
} IA32_QM_EVTSEL_REGISTER;

/**
 * @brief Monitoring Counter Register. <b>(R/O)</b>
 */
#define IA32_QM_CTR                                                  0x00000C8E

typedef union
{
  struct
  {
    UINT64 ResourceMonitoredData                                   : 62;
    UINT64 Unavailable                                             : 1;
    UINT64 Error                                                   : 1;
  };

  UINT64 Flags;
} IA32_QM_CTR_REGISTER;

/**
 * @brief Resource Association Register. <b>(R/W)</b>
 */
#define IA32_PQR_ASSOC                                               0x00000C8F

typedef union
{
  struct
  {
    UINT64 ResourceMonitoringId                                    : 32;
    UINT64 Cos                                                     : 32;
  };

  UINT64 Flags;
} IA32_PQR_ASSOC_REGISTER;

/**
 * @brief Supervisor State of MPX Configuration. <b>(R/W)</b>
 */
#define IA32_BNDCFGS                                                 0x00000D90

typedef union
{
  struct
  {
    UINT64 Enable                                                  : 1;
    UINT64 BndPreserve                                             : 1;
    UINT64 Reserved1                                               : 10;
    UINT64 BoundDirectoryBaseAddress                               : 52;
  };

  UINT64 Flags;
} IA32_BNDCFGS_REGISTER;

/**
 * @brief Extended Supervisor State Mask. <b>(R/W)</b>
 */
#define IA32_XSS                                                     0x00000DA0

typedef union
{
  struct
  {
    UINT64 Reserved1                                               : 8;
    UINT64 TracePacketConfigurationState                           : 1;
  };

  UINT64 Flags;
} IA32_XSS_REGISTER;

/**
 * @brief Package Level Enable/disable HDC. <b>(R/W)</b>
 */
#define IA32_PKG_HDC_CTL                                             0x00000DB0

typedef union
{
  struct
  {
    UINT64 HdcPkgEnable                                            : 1;
  };

  UINT64 Flags;
} IA32_PKG_HDC_CTL_REGISTER;

/**
 * @brief Enable/disable HWP. <b>(R/W)</b>
 */
#define IA32_PM_CTL1                                                 0x00000DB1

typedef union
{
  struct
  {
    UINT64 HdcAllowBlock                                           : 1;
  };

  UINT64 Flags;
} IA32_PM_CTL1_REGISTER;

/**
 * @brief Per-Logical_Processor HDC Idle Residency. <b>(R/0)</b>
 */
#define IA32_THREAD_STALL                                            0x00000DB2

typedef struct
{
  UINT64 StallCycleCount;
} IA32_THREAD_STALL_REGISTER;

/**
 * @brief Extended Feature Enables.
 */
#define IA32_EFER                                                    0xC0000080

typedef union
{
  struct
  {
    UINT64 SyscallEnable                                           : 1;
    UINT64 Reserved1                                               : 7;
    UINT64 Ia32EModeEnable                                         : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 Ia32EModeActive                                         : 1;
    UINT64 ExecuteDisableBitEnable                                 : 1;
  };

  UINT64 Flags;
} IA32_EFER_REGISTER;

/**
 * @brief System Call Target Address. <b>(R/W)</b>
 */
#define IA32_STAR                                                    0xC0000081

/**
 * @brief Target RIP for the called procedure when SYSCALL is executed in 64-bit mode. <b>(R/W)</b>
 */
#define IA32_LSTAR                                                   0xC0000082

/**
 * @brief Not used, as the SYSCALL instruction is not recognized in compatibility mode. <b>(R/W)</b>
 */
#define IA32_CSTAR                                                   0xC0000083

/**
 * @brief System Call Flag Mask. <b>(R/W)</b>
 */
#define IA32_FMASK                                                   0xC0000084

/**
 * @brief Map of BASE Address of FS. <b>(R/W)</b>
 */
#define IA32_FS_BASE                                                 0xC0000100

/**
 * @brief Map of BASE Address of GS. <b>(R/W)</b>
 */
#define IA32_GS_BASE                                                 0xC0000101

/**
 * @brief Swap Target of BASE Address of GS. <b>(R/W)</b>
 */
#define IA32_KERNEL_GS_BASE                                          0xC0000102

/**
 * @brief Auxiliary TSC. <b>(RW)</b>
 */
#define IA32_TSC_AUX                                                 0xC0000103

typedef union
{
  struct
  {
    UINT64 TscAuxiliarySignature                                   : 32;
  };

  UINT64 Flags;
} IA32_TSC_AUX_REGISTER;

/**
 * @}
 */

/**
 * @defgroup PAGING \
 *           Paging
 * @{
 */
/**
 * @defgroup PAGING_32 \
 *           32-Bit Paging
 *
 * A logical processor uses 32-bit paging if CR0.PG = 1 and CR4.PAE = 0. 32-bit paging translates 32-bit linear addresses
 * to 40-bit physical addresses. Although 40 bits corresponds to 1 TByte, linear addresses are limited to 32 bits; at most
 * 4 GBytes of linear-address space may be accessed at any given time.
 * 32-bit paging uses a hierarchy of paging structures to produce a translation for a linear address. CR3 is used to locate
 * the first paging-structure, the page directory. 32-bit paging may map linear addresses to either 4-KByte pages or
 * 4-MByte pages.
 *
 * @see Vol3A[4.5(4-LEVEL PAGING)] (reference)
 * @{
 */
/**
 * @brief Format of a 32-Bit Page-Directory Entry that Maps a 4-MByte Page
 */
typedef union
{
  struct
  {
    UINT32 Present                                                 : 1;
    UINT32 Write                                                   : 1;
    UINT32 Supervisor                                              : 1;
    UINT32 PageLevelWriteThrough                                   : 1;
    UINT32 PageLevelCacheDisable                                   : 1;
    UINT32 Accessed                                                : 1;
    UINT32 Dirty                                                   : 1;
    UINT32 LargePage                                               : 1;
    UINT32 Global                                                  : 1;
    UINT32 Ignored1                                                : 3;
    UINT32 Pat                                                     : 1;
    UINT32 PageFrameNumberLow                                      : 8;
    UINT32 Reserved1                                               : 1;
    UINT32 PageFrameNumberHigh                                     : 10;
  };

  UINT32 Flags;
} PDE_4MB_32;

/**
 * @brief Format of a 32-Bit Page-Directory Entry that References a Page Table
 */
typedef union
{
  struct
  {
    UINT32 Present                                                 : 1;
    UINT32 Write                                                   : 1;
    UINT32 Supervisor                                              : 1;
    UINT32 PageLevelWriteThrough                                   : 1;
    UINT32 PageLevelCacheDisable                                   : 1;
    UINT32 Accessed                                                : 1;
    UINT32 Ignored1                                                : 1;
    UINT32 LargePage                                               : 1;
    UINT32 Ignored2                                                : 4;
    UINT32 PageFrameNumber                                         : 20;
  };

  UINT32 Flags;
} PDE_32;

/**
 * @brief Format of a 32-Bit Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    UINT32 Present                                                 : 1;
    UINT32 Write                                                   : 1;
    UINT32 Supervisor                                              : 1;
    UINT32 PageLevelWriteThrough                                   : 1;
    UINT32 PageLevelCacheDisable                                   : 1;
    UINT32 Accessed                                                : 1;
    UINT32 Dirty                                                   : 1;
    UINT32 Pat                                                     : 1;
    UINT32 Global                                                  : 1;
    UINT32 Ignored1                                                : 3;
    UINT32 PageFrameNumber                                         : 20;
  };

  UINT32 Flags;
} PTE_32;

/**
 * @brief Format of a common Page-Table Entry
 */
typedef union
{
  struct
  {
    UINT32 Present                                                 : 1;
    UINT32 Write                                                   : 1;
    UINT32 Supervisor                                              : 1;
    UINT32 PageLevelWriteThrough                                   : 1;
    UINT32 PageLevelCacheDisable                                   : 1;
    UINT32 Accessed                                                : 1;
    UINT32 Dirty                                                   : 1;
    UINT32 LargePage                                               : 1;
    UINT32 Global                                                  : 1;
    UINT32 Ignored1                                                : 3;
    UINT32 PageFrameNumber                                         : 20;
  };

  UINT32 Flags;
} PT_ENTRY_32;

/**
 * @}
 */

/**
 * @defgroup PAGING_64 \
 *           64-Bit (4-Level Paging)
 *
 * A logical processor uses 4-level paging if CR0.PG = 1, CR4.PAE = 1, and IA32_EFER.LME = 1. With 4-level paging, linear
 * address are translated using a hierarchy of in-memory paging structures located using the contents of CR3. 4-level
 * paging translates 48-bit linear addresses to 52-bit physical addresses. Although 52 bits corresponds to 4 PBytes, linear
 * addresses are limited to 48 bits; at most 256 TBytes of linear-address space may be accessed at any given time.
 * 4-level paging uses a hierarchy of paging structures to produce a translation for a linear address. CR3 is used to
 * locate the first paging-structure, the PML4 table. Use of CR3 with 4-level paging depends on whether processcontext
 * identifiers (PCIDs) have been enabled by setting CR4.PCIDE.
 *
 * @see Vol3A[4.5(4-LEVEL PAGING)] (reference)
 * @{
 */
/**
 * @brief Format of a 4-Level PML4 Entry (PML4E) that References a Page-Directory-Pointer Table
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 MustBeZero                                              : 1;
    UINT64 Ignored1                                                : 4;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved2                                               : 4;
    UINT64 Ignored2                                                : 11;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PML4E;

/**
 * @brief Format of a 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Global                                                  : 1;
    UINT64 Ignored1                                                : 3;
    UINT64 Pat                                                     : 1;
    UINT64 Reserved1                                               : 17;
    UINT64 PageFrameNumber                                         : 18;
    UINT64 Reserved2                                               : 4;
    UINT64 Ignored2                                                : 7;
    UINT64 ProtectionKey                                           : 4;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PDPTE_1GB;

/**
 * @brief Format of a 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that References a Page Directory
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Ignored1                                                : 4;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved2                                               : 4;
    UINT64 Ignored2                                                : 11;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PDPTE;

/**
 * @brief Format of a 4-Level Page-Directory Entry that Maps a 2-MByte Page
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Global                                                  : 1;
    UINT64 Ignored1                                                : 3;
    UINT64 Pat                                                     : 1;
    UINT64 Reserved1                                               : 17;
    UINT64 PageFrameNumber                                         : 18;
    UINT64 Reserved2                                               : 4;
    UINT64 Ignored2                                                : 7;
    UINT64 ProtectionKey                                           : 4;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PDE_2MB;

/**
 * @brief Format of a 4-Level Page-Directory Entry that References a Page Table
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Ignored1                                                : 4;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved2                                               : 4;
    UINT64 Ignored2                                                : 11;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PDE;

/**
 * @brief Format of a 4-Level Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 Pat                                                     : 1;
    UINT64 Global                                                  : 1;
    UINT64 Ignored1                                                : 3;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved1                                               : 4;
    UINT64 Ignored2                                                : 7;
    UINT64 ProtectionKey                                           : 4;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PTE;

/**
 * @brief Format of a common Page-Table Entry
 */
typedef union
{
  struct
  {
    UINT64 Present                                                 : 1;
    UINT64 Write                                                   : 1;
    UINT64 Supervisor                                              : 1;
    UINT64 PageLevelWriteThrough                                   : 1;
    UINT64 PageLevelCacheDisable                                   : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Global                                                  : 1;
    UINT64 Ignored1                                                : 3;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved1                                               : 4;
    UINT64 Ignored2                                                : 7;
    UINT64 ProtectionKey                                           : 4;
    UINT64 ExecuteDisable                                          : 1;
  };

  UINT64 Flags;
} PT_ENTRY;

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup SEGMENT_DESCRIPTORS \
 *           Segment descriptors
 * @{
 */
/**
 * @brief Pseudo-Descriptor Format (32-bit)
 */
#include <pshpack1.h>
typedef struct
{
  UINT16 Limit;
  UINT32 BaseAddress;
} DESCRIPTOR_32;
#include <poppack.h>

/**
 * @brief Pseudo-Descriptor Format (64-bit)
 */
#include <pshpack1.h>
typedef struct
{
  UINT16 Limit;
  UINT64 BaseAddress;
} DESCRIPTOR_64;
#include <poppack.h>

/**
 * @brief General Segment Descriptor (32-bit)
 *
 * A segment descriptor is a data structure in a GDT or LDT that provides the processor with the size and location of a
 * segment, as well as access control and status information. Segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 */
typedef struct
{
  UINT16 SegmentLimitLow;
  UINT16 BaseAddressLow;
  /**
   * @brief Segment descriptor fields
   */
  union
  {
    struct
    {
      UINT32 BaseAddressMiddle                                     : 8;
      UINT32 Type                                                  : 4;
      UINT32 DescriptorType                                        : 1;
      UINT32 DescriptorPrivilegeLevel                              : 2;
      UINT32 Present                                               : 1;
      UINT32 SegmentLimitHigh                                      : 4;
      UINT32 System                                                : 1;
      UINT32 LongMode                                              : 1;
      UINT32 DefaultBig                                            : 1;
      UINT32 Granularity                                           : 1;
      UINT32 BaseAddressHigh                                       : 8;
    };

    UINT32 Flags;
  } Bits;

} SEGMENT_DESCRIPTOR_32;

/**
 * @brief General Segment Descriptor (64-bit)
 *
 * A segment descriptor is a data structure in a GDT or LDT that provides the processor with the size and location of a
 * segment, as well as access control and status information. Segment descriptors are typically created by compilers,
 * linkers, loaders, or the operating system or executive, but not application programs.
 */
typedef struct
{
  UINT16 SegmentLimitLow;
  UINT16 BaseAddressLow;
  /**
   * @brief Segment descriptor fields
   */
  union
  {
    struct
    {
      UINT32 BaseAddressMiddle                                     : 8;
      UINT32 Type                                                  : 4;
      UINT32 DescriptorType                                        : 1;
      UINT32 DescriptorPrivilegeLevel                              : 2;
      UINT32 Present                                               : 1;
      UINT32 SegmentLimitHigh                                      : 4;
      UINT32 System                                                : 1;
      UINT32 LongMode                                              : 1;
      UINT32 DefaultBig                                            : 1;
      UINT32 Granularity                                           : 1;
      UINT32 BaseAddressHigh                                       : 8;
    };

    UINT32 Flags;
  } Bits;

  UINT32 BaseAddressUpper;
  UINT32 MustBeZero;
} SEGMENT_DESCRIPTOR_64;

/**
 * @defgroup CODE_AND_DATA_SEGMENT_DESCRIPTOR_TYPE \
 *           Code- and Data-Segment Descriptor Types
 *
 * When the S (descriptor type) flag in a segment descriptor is set, the descriptor is for either a code or a data segment.
 * The highest order bit of the type field (bit 11 of the second double word of the segment descriptor) then determines
 * whether the descriptor is for a data segment (clear) or a code segment (set). For data segments, the three low-order
 * bits of the type field (bits 8, 9, and 10) are interpreted as accessed (A), write-enable (W), and expansion-direction
 * (E). See Table 3-1 for a description of the encoding of the bits in the type field for code and data segments. Data
 * segments can be read-only or read/write segments, depending on the setting of the write-enable bit.
 *
 * @see Vol3A[3.4.5.1(Code- and Data-Segment Descriptor Types)] (reference)
 * @{
 */
/**
 * @brief Read-Only.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY                               0x00000000

/**
 * @brief Data Read-Only, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_ACCESSED                      0x00000001

/**
 * @brief Data Read/Write.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE                              0x00000002

/**
 * @brief Data Read/Write, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_ACCESSED                     0x00000003

/**
 * @brief Data Read-Only, expand-down.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_EXPAND_DOWN                   0x00000004

/**
 * @brief Data Read-Only, expand-down, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_ONLY_EXPAND_DOWN_ACCESSED          0x00000005

/**
 * @brief Data Read/Write, expand-down.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_EXPAND_DOWN                  0x00000006

/**
 * @brief Data Read/Write, expand-down, accessed.
 */
#define DESCRIPTOR_TYPE_DATA_READ_WRITE_EXPAND_DOWN_ACCESSED         0x00000007

/**
 * @brief Code Execute-Only.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY                            0x00000008

/**
 * @brief Code Execute-Only, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_ACCESSED                   0x00000009

/**
 * @brief Code Execute/Read.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ                            0x0000000A

/**
 * @brief Code Execute/Read, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_ACCESSED                   0x0000000B

/**
 * @brief Code Execute-Only, conforming.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_CONFORMING                 0x0000000C

/**
 * @brief Code Execute-Only, conforming, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_ONLY_CONFORMING_ACCESSED        0x0000000D

/**
 * @brief Code Execute/Read, conforming.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_CONFORMING                 0x0000000E

/**
 * @brief Code Execute/Read, conforming, accessed.
 */
#define DESCRIPTOR_TYPE_CODE_EXECUTE_READ_CONFORMING_ACCESSED        0x0000000F

/**
 * @}
 */

/**
 * @defgroup SYSTEM_DESCRIPTOR_TYPE \
 *           System Descriptor Types
 *
 * When the S (descriptor type) flag in a segment descriptor is clear, the descriptor type is a system descriptor. The
 * processor recognizes the following types of system descriptors:
 * - Local descriptor-table (LDT) segment descriptor.
 * - Task-state segment (TSS) descriptor.
 * - Call-gate descriptor.
 * - Interrupt-gate descriptor.
 * - Trap-gate descriptor.
 * - Task-gate descriptor.
 * These descriptor types fall into two categories: system-segment descriptors and gate descriptors. Systemsegment
 * descriptors point to system segments (LDT and TSS segments). Gate descriptors are in themselves "gates," which hold
 * pointers to procedure entry points in code segments (call, interrupt, and trap gates) or which hold segment selectors
 * for TSS's (task gates).
 *
 * @see Vol3A[3.5(SYSTEM DESCRIPTOR TYPES)] (reference)
 * @{
 */
/**
 * @brief - 32-Bit Mode: Reserved
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_1                                   0x00000000

/**
 * @brief - 32-Bit Mode: 16-bit TSS (Available)
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TSS_16_AVAILABLE                             0x00000001

/**
 * @brief - 32-Bit Mode: LDT
 *        - IA-32e Mode: LDT
 */
#define DESCRIPTOR_TYPE_LDT                                          0x00000002

/**
 * @brief - 32-Bit Mode: 16-bit TSS (Busy)
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TSS_16_BUSY                                  0x00000003

/**
 * @brief - 32-Bit Mode: 16-bit Call Gate
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_CALL_GATE_16                                 0x00000004

/**
 * @brief - 32-Bit Mode: Task Gate
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TASK_GATE                                    0x00000005

/**
 * @brief - 32-Bit Mode: 16-bit Interrupt Gate
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_INTERRUPT_GATE_16                            0x00000006

/**
 * @brief - 32-Bit Mode: 16-bit Trap Gate
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_TRAP_GATE_16                                 0x00000007

/**
 * @brief - 32-Bit Mode: Reserved
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_2                                   0x00000008

/**
 * @brief - 32-Bit Mode: 32-bit TSS (Available)
 *        - IA-32e Mode: 64-bit TSS (Available)
 */
#define DESCRIPTOR_TYPE_TSS_AVAILABLE                                0x00000009

/**
 * @brief - 32-Bit Mode: Reserved
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_3                                   0x0000000A

/**
 * @brief - 32-Bit Mode: 32-bit TSS (Busy)
 *        - IA-32e Mode: 64-bit TSS (Busy)
 */
#define DESCRIPTOR_TYPE_TSS_BUSY                                     0x0000000B

/**
 * @brief - 32-Bit Mode: 32-bit Call Gate
 *        - IA-32e Mode: 64-bit Call Gate
 */
#define DESCRIPTOR_TYPE_CALL_GATE                                    0x0000000C

/**
 * @brief - 32-Bit Mode: Reserved
 *        - IA-32e Mode: Reserved
 */
#define DESCRIPTOR_TYPE_RESERVED_4                                   0x0000000D

/**
 * @brief - 32-Bit Mode: 32-bit Interrupt Gate
 *        - IA-32e Mode: 64-bit Interrupt Gate
 */
#define DESCRIPTOR_TYPE_INTERRUPT_GATE                               0x0000000E

/**
 * @brief - 32-Bit Mode: 32-bit Trap Gate
 *        - IA-32e Mode: 64-bit Trap Gate
 */
#define DESCRIPTOR_TYPE_TRAP_GATE                                    0x0000000F

/**
 * @}
 */

/**
 * @brief A segment selector is a 16-bit identifier for a segment. It does not point directly to the segment, but instead
 *        points to the segment descriptor that defines the segment
 */
typedef union
{
  struct
  {
    UINT16 RequestPrivilegeLevel                                   : 2;
    UINT16 Table                                                   : 1;
    UINT16 Index                                                   : 14;
  };

  UINT16 Flags;
} SELECTOR;

/**
 * @}
 */

/**
 * @defgroup VMX \
 *           VMX
 * @{
 */
/**
 * @defgroup VMX_BASIC_EXIT_REASONS \
 *           VMX Basic Exit Reasons
 *
 * VMX Basic Exit Reasons.
 *
 * @see Vol3D[C(VMX BASIC EXIT REASONS)] (reference)
 * @{
 */
/**
 * @brief Either:
 *        -# Guest software caused an exception and the bit in the exception bitmap associated with exception's vector was 1. This
 *        case includes executions of BOUND that cause \#BR, executions of INT1 (they cause \#DB), executions of INT3 (they cause
 *        \#BP), executions of INTO that cause \#OF, and executions of UD0, UD1, and UD2 (they cause \#UD).
 *        -# An NMI was delivered to the logical processor and the "NMI exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXCEPTION_OR_NMI                             0x00000000

/**
 * @brief An external interrupt arrived and the "external-interrupt exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXTERNAL_INTERRUPT                           0x00000001

/**
 * @brief The logical processor encountered an exception while attempting to call the double-fault handler and that
 *        exception did not itself cause a VM exit due to the exception bitmap.
 */
#define VMX_EXIT_REASON_TRIPLE_FAULT                                 0x00000002

/**
 * @brief An INIT signal arrived.
 */
#define VMX_EXIT_REASON_INIT_SIGNAL                                  0x00000003

/**
 * @brief A SIPI arrived while the logical processor was in the "wait-for-SIPI" state.
 */
#define VMX_EXIT_REASON_STARTUP_IPI                                  0x00000004

/**
 * @brief An SMI arrived immediately after retirement of an I/O instruction and caused an SMM VM exit.
 */
#define VMX_EXIT_REASON_IO_SMI                                       0x00000005

/**
 * @brief An SMI arrived and caused an SMM VM exit but not immediately after retirement of an I/O instruction.
 */
#define VMX_EXIT_REASON_SMI                                          0x00000006

/**
 * @brief At the beginning of an instruction, RFLAGS.IF was 1; events were not blocked by STI or by MOV SS; and the
 *        "interrupt-window exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_INTERRUPT_WINDOW                             0x00000007

/**
 * @brief At the beginning of an instruction, there was no virtual-NMI blocking; events were not blocked by MOV SS; and the
 *        "NMI-window exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_NMI_WINDOW                                   0x00000008

/**
 * @brief Guest software attempted a task switch.
 */
#define VMX_EXIT_REASON_TASK_SWITCH                                  0x00000009

/**
 * @brief Guest software attempted to execute CPUID.
 */
#define VMX_EXIT_REASON_EXECUTE_CPUID                                0x0000000A

/**
 * @brief Guest software attempted to execute GETSEC.
 */
#define VMX_EXIT_REASON_EXECUTE_GETSEC                               0x0000000B

/**
 * @brief Guest software attempted to execute HLT and the "HLT exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_HLT                                  0x0000000C

/**
 * @brief Guest software attempted to execute INVD.
 */
#define VMX_EXIT_REASON_EXECUTE_INVD                                 0x0000000D

/**
 * @brief Guest software attempted to execute INVLPG and the "INVLPG exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_INVLPG                               0x0000000E

/**
 * @brief Guest software attempted to execute RDPMC and the "RDPMC exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDPMC                                0x0000000F

/**
 * @brief Guest software attempted to execute RDTSC and the "RDTSC exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDTSC                                0x00000010

/**
 * @brief Guest software attempted to execute RSM in SMM.
 */
#define VMX_EXIT_REASON_EXECUTE_RSM_IN_SMM                           0x00000011

/**
 * @brief VMCALL was executed either by guest software (causing an ordinary VM exit) or by the executive monitor (causing
 *        an SMM VM exit).
 */
#define VMX_EXIT_REASON_EXECUTE_VMCALL                               0x00000012

/**
 * @brief Guest software attempted to execute VMCLEAR.
 */
#define VMX_EXIT_REASON_EXECUTE_VMCLEAR                              0x00000013

/**
 * @brief Guest software attempted to execute VMLAUNCH.
 */
#define VMX_EXIT_REASON_EXECUTE_VMLAUNCH                             0x00000014

/**
 * @brief Guest software attempted to execute VMPTRLD.
 */
#define VMX_EXIT_REASON_EXECUTE_VMPTRLD                              0x00000015

/**
 * @brief Guest software attempted to execute VMPTRST.
 */
#define VMX_EXIT_REASON_EXECUTE_VMPTRST                              0x00000016

/**
 * @brief Guest software attempted to execute VMREAD.
 */
#define VMX_EXIT_REASON_EXECUTE_VMREAD                               0x00000017

/**
 * @brief Guest software attempted to execute VMRESUME.
 */
#define VMX_EXIT_REASON_EXECUTE_VMRESUME                             0x00000018

/**
 * @brief Guest software attempted to execute VMWRITE.
 */
#define VMX_EXIT_REASON_EXECUTE_VMWRITE                              0x00000019

/**
 * @brief Guest software attempted to execute VMXOFF.
 */
#define VMX_EXIT_REASON_EXECUTE_VMXOFF                               0x0000001A

/**
 * @brief Guest software attempted to execute VMXON.
 */
#define VMX_EXIT_REASON_EXECUTE_VMXON                                0x0000001B

/**
 * @brief Guest software attempted to access CR0, CR3, CR4, or CR8 using CLTS, LMSW, or MOV CR and the VM-execution control
 *        fields indicate that a VM exit should occur. This basic exit reason is not used for trap-like VM exits following
 *        executions of the MOV to CR8 instruction when the "use TPR shadow" VM-execution control is 1. Such VM exits instead use
 *        basic exit reason 43.
 */
#define VMX_EXIT_REASON_MOV_CR                                       0x0000001C

/**
 * @brief Guest software attempted a MOV to or from a debug register and the "MOV-DR exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_MOV_DR                                       0x0000001D

/**
 * @brief Guest software attempted to execute an I/O instruction and either:
 *        -# The "use I/O bitmaps" VM-execution control was 0 and the "unconditional I/O exiting" VM-execution control was 1.
 *        -# The "use I/O bitmaps" VM-execution control was 1 and a bit in the I/O bitmap associated with one of the ports
 *        accessed by the I/O instruction was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_IO_INSTRUCTION                       0x0000001E

/**
 * @brief Guest software attempted to execute RDMSR and either:
 *        -# The "use MSR bitmaps" VM-execution control was 0.
 *        -# The value of RCX is neither in the range 00000000H - 00001FFFH nor in the range C0000000H - C0001FFFH.
 *        -# The value of RCX was in the range 00000000H - 00001FFFH and the nth bit in read bitmap for low MSRs is 1, where n was
 *        the value of RCX.
 *        -# The value of RCX is in the range C0000000H - C0001FFFH and the nth bit in read bitmap for high MSRs is 1, where n is
 *        the value of RCX & 00001FFFH.
 */
#define VMX_EXIT_REASON_EXECUTE_RDMSR                                0x0000001F

/**
 * @brief Guest software attempted to execute WRMSR and either:
 *        -# The "use MSR bitmaps" VM-execution control was 0.
 *        -# The value of RCX is neither in the range 00000000H - 00001FFFH nor in the range C0000000H - C0001FFFH.
 *        -# The value of RCX was in the range 00000000H - 00001FFFH and the nth bit in write bitmap for low MSRs is 1, where n
 *        was the value of RCX.
 *        -# The value of RCX is in the range C0000000H - C0001FFFH and the nth bit in write bitmap for high MSRs is 1, where n is
 *        the value of RCX & 00001FFFH.
 */
#define VMX_EXIT_REASON_EXECUTE_WRMSR                                0x00000020

/**
 * @brief A VM entry failed one of the checks identified in Section 26.3.1.
 */
#define VMX_EXIT_REASON_ERROR_INVALID_GUEST_STATE                    0x00000021

/**
 * @brief A VM entry failed in an attempt to load MSRs. See Section 26.4.
 */
#define VMX_EXIT_REASON_ERROR_MSR_LOAD                               0x00000022

/**
 * @brief Guest software attempted to execute MWAIT and the "MWAIT exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_MWAIT                                0x00000024

/**
 * @brief A VM entry occurred due to the 1-setting of the "monitor trap flag" VM-execution control and injection of an MTF
 *        VM exit as part of VM entry.
 */
#define VMX_EXIT_REASON_MONITOR_TRAP_FLAG                            0x00000025

/**
 * @brief Guest software attempted to execute MONITOR and the "MONITOR exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_MONITOR                              0x00000027

/**
 * @brief Either guest software attempted to execute PAUSE and the "PAUSE exiting" VM-execution control was 1 or the
 *        "PAUSE-loop exiting" VM-execution control was 1 and guest software executed a PAUSE loop with execution time exceeding
 *        PLE_Window.
 */
#define VMX_EXIT_REASON_EXECUTE_PAUSE                                0x00000028

/**
 * @brief A machine-check event occurred during VM entry.
 */
#define VMX_EXIT_REASON_ERROR_MACHINE_CHECK                          0x00000029

/**
 * @brief The logical processor determined that the value of bits 7:4 of the byte at offset 080H on the virtual-APIC page
 *        was below that of the TPR threshold VM-execution control field while the "use TPR shadow" VMexecution control was 1
 *        either as part of TPR virtualization or VM entry.
 */
#define VMX_EXIT_REASON_TPR_BELOW_THRESHOLD                          0x0000002B

/**
 * @brief Guest software attempted to access memory at a physical address on the APIC-access page and the "virtualize APIC
 *        accesses" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_APIC_ACCESS                                  0x0000002C

/**
 * @brief EOI virtualization was performed for a virtual interrupt whose vector indexed a bit set in the EOIexit bitmap.
 */
#define VMX_EXIT_REASON_VIRTUALIZED_EOI                              0x0000002D

/**
 * @brief Guest software attempted to execute LGDT, LIDT, SGDT, or SIDT and the "descriptor-table exiting" VM-execution
 *        control was 1.
 */
#define VMX_EXIT_REASON_GDTR_IDTR_ACCESS                             0x0000002E

/**
 * @brief Guest software attempted to execute LLDT, LTR, SLDT, or STR and the "descriptor-table exiting" VM-execution
 *        control was 1.
 */
#define VMX_EXIT_REASON_LDTR_TR_ACCESS                               0x0000002F

/**
 * @brief An attempt to access memory with a guest-physical address was disallowed by the configuration of the EPT paging
 *        structures.
 */
#define VMX_EXIT_REASON_EPT_VIOLATION                                0x00000030

/**
 * @brief An attempt to access memory with a guest-physical address encountered a misconfigured EPT paging-structure entry.
 */
#define VMX_EXIT_REASON_EPT_MISCONFIGURATION                         0x00000031

/**
 * @brief Guest software attempted to execute INVEPT.
 */
#define VMX_EXIT_REASON_EXECUTE_INVEPT                               0x00000032

/**
 * @brief Guest software attempted to execute RDTSCP and the "enable RDTSCP" and "RDTSC exiting" VM-execution controls were
 *        both 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDTSCP                               0x00000033

/**
 * @brief The preemption timer counted down to zero.
 */
#define VMX_EXIT_REASON_VMX_PREEMPTION_TIMER_EXPIRED                 0x00000034

/**
 * @brief Guest software attempted to execute INVVPID.
 */
#define VMX_EXIT_REASON_EXECUTE_INVVPID                              0x00000035

/**
 * @brief Guest software attempted to execute WBINVD and the "WBINVD exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_WBINVD                               0x00000036

/**
 * @brief Guest software attempted to execute XSETBV.
 */
#define VMX_EXIT_REASON_EXECUTE_XSETBV                               0x00000037

/**
 * @brief Guest software completed a write to the virtual-APIC page that must be virtualized by VMM software.
 */
#define VMX_EXIT_REASON_APIC_WRITE                                   0x00000038

/**
 * @brief Guest software attempted to execute RDRAND and the "RDRAND exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDRAND                               0x00000039

/**
 * @brief Guest software attempted to execute INVPCID and the "enable INVPCID" and "INVLPG exiting" VM-execution controls
 *        were both 1.
 */
#define VMX_EXIT_REASON_EXECUTE_INVPCID                              0x0000003A

/**
 * @brief Guest software invoked a VM function with the VMFUNC instruction and the VM function either was not enabled or
 *        generated a function-specific condition causing a VM exit.
 */
#define VMX_EXIT_REASON_EXECUTE_VMFUNC                               0x0000003B

/**
 * @brief Guest software attempted to execute ENCLS and "enable ENCLS exiting" VM-execution control was 1 and either:
 *        -# EAX < 63 and the corresponding bit in the ENCLS-exiting bitmap is 1; or
 *        -# EAX >= 63 and bit 63 in the ENCLS-exiting bitmap is 1.
 */
#define VMX_EXIT_REASON_EXECUTE_ENCLS                                0x0000003C

/**
 * @brief Guest software attempted to execute RDSEED and the "RDSEED exiting" VM-execution control was 1.
 */
#define VMX_EXIT_REASON_EXECUTE_RDSEED                               0x0000003D

/**
 * @brief The processor attempted to create a page-modification log entry and the value of the PML index was not in the
 *        range 0-511.
 */
#define VMX_EXIT_REASON_PAGE_MODIFICATION_LOG_FULL                   0x0000003E

/**
 * @brief Guest software attempted to execute XSAVES, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the
 *        logical-AND of the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
 */
#define VMX_EXIT_REASON_EXECUTE_XSAVES                               0x0000003F

/**
 * @brief Guest software attempted to execute XRSTORS, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the
 *        logical-AND of the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
 */
#define VMX_EXIT_REASON_EXECUTE_XRSTORS                              0x00000040

/**
 * @}
 */

/**
 * @defgroup VMX_INSTRUCTION_ERROR_NUMBERS \
 *           VM Instruction Error Numbers
 *
 * VM Instruction Error Numbers.
 *
 * @see Vol3C[30.4(VM INSTRUCTION ERROR NUMBERS)] (reference)
 * @{
 */
/**
 * @brief VMCALL executed in VMX root operation.
 */
#define VMX_ERROR_VMCALL_IN_VMX_ROOT_OPERATION                       0x00000001

/**
 * @brief VMCLEAR with invalid physical address.
 */
#define VMX_ERROR_VMCLEAR_INVALID_PHYSICAL_ADDRESS                   0x00000002

/**
 * @brief VMCLEAR with VMXON pointer.
 */
#define VMX_ERROR_VMCLEAR_INVALID_VMXON_POINTER                      0x00000003

/**
 * @brief VMLAUNCH with non-clear VMCS.
 */
#define VMX_ERROR_VMLAUCH_NON_CLEAR_VMCS                             0x00000004

/**
 * @brief VMRESUME with non-launched VMCS.
 */
#define VMX_ERROR_VMRESUME_NON_LAUNCHED_VMCS                         0x00000005

/**
 * @brief VMRESUME after VMXOFF (VMXOFF and VMXON between VMLAUNCH and VMRESUME).
 */
#define VMX_ERROR_VMRESUME_AFTER_VMXOFF                              0x00000006

/**
 * @brief VM entry with invalid control field(s).
 */
#define VMX_ERROR_VMENTRY_INVALID_CONTROL_FIELDS                     0x00000007

/**
 * @brief VM entry with invalid host-state field(s).
 */
#define VMX_ERROR_VMENTRY_INVALID_HOST_STATE                         0x00000008

/**
 * @brief VMPTRLD with invalid physical address.
 */
#define VMX_ERROR_VMPTRLD_INVALID_PHYSICAL_ADDRESS                   0x00000009

/**
 * @brief VMPTRLD with VMXON pointer.
 */
#define VMX_ERROR_VMPTRLD_VMXON_POINTER                              0x0000000A

/**
 * @brief VMPTRLD with incorrect VMCS revision identifier.
 */
#define VMX_ERROR_VMPTRLD_INCORRECT_VMCS_REVISION_ID                 0x0000000B

/**
 * @brief VMREAD/VMWRITE from/to unsupported VMCS component.
 */
#define VMX_ERROR_VMREAD_VMWRITE_INVALID_COMPONENT                   0x0000000C

/**
 * @brief VMWRITE to read-only VMCS component.
 */
#define VMX_ERROR_VMWRITE_READONLY_COMPONENT                         0x0000000D

/**
 * @brief VMXON executed in VMX root operation.
 */
#define VMX_ERROR_VMXON_IN_VMX_ROOT_OP                               0x0000000F

/**
 * @brief VM entry with invalid executive-VMCS pointer.
 */
#define VMX_ERROR_VMENTRY_INVALID_VMCS_EXECUTIVE_POINTER             0x00000010

/**
 * @brief VM entry with non-launched executive VMCS.
 */
#define VMX_ERROR_VMENTRY_NON_LAUNCHED_EXECUTIVE_VMCS                0x00000011

/**
 * @brief VM entry with executive-VMCS pointer not VMXON pointer (when attempting to deactivate the dual-monitor treatment
 *        of SMIs and SMM).
 */
#define VMX_ERROR_VMENTRY_EXECUTIVE_VMCS_PTR                         0x00000012

/**
 * @brief VMCALL with non-clear VMCS (when attempting to activate the dual-monitor treatment of SMIs and SMM).
 */
#define VMX_ERROR_VMCALL_NON_CLEAR_VMCS                              0x00000013

/**
 * @brief VMCALL with invalid VM-exit control fields.
 */
#define VMX_ERROR_VMCALL_INVALID_VMEXIT_FIELDS                       0x00000014

/**
 * @brief VMCALL with incorrect MSEG revision identifier (when attempting to activate the dual-monitor treatment of SMIs
 *        and SMM).
 */
#define VMX_ERROR_VMCALL_INVALID_MSEG_REVISION_ID                    0x00000016

/**
 * @brief VMXOFF under dual-monitor treatment of SMIs and SMM.
 */
#define VMX_ERROR_VMXOFF_DUAL_MONITOR                                0x00000017

/**
 * @brief VMCALL with invalid SMM-monitor features (when attempting to activate the dual-monitor treatment of SMIs and
 *        SMM).
 */
#define VMX_ERROR_VMCALL_INVALID_SMM_MONITOR                         0x00000018

/**
 * @brief VM entry with invalid VM-execution control fields in executive VMCS (when attempting to return from SMM).
 */
#define VMX_ERROR_VMENTRY_INVALID_VM_EXECUTION_CONTROL               0x00000019

/**
 * @brief VM entry with events blocked by MOV SS.
 */
#define VMX_ERROR_VMENTRY_MOV_SS                                     0x0000001A

/**
 * @brief Invalid operand to INVEPT/INVVPID.
 */
#define VMX_ERROR_INVEPT_INVVPID_INVALID_OPERAND                     0x0000001C

/**
 * @}
 */

/**
 * @defgroup VMX_EXCEPTIONS \
 *           Virtualization Exceptions
 *
 * Virtualization Exceptions.
 *
 * @see Vol3C[25.5.6(Virtualization Exceptions)] (reference)
 * @{
 */
typedef struct
{
  UINT32 Reason;
  UINT32 ExceptionMask;
  UINT64 Exit;
  UINT64 GuestLinearAddress;
  UINT64 GuestPhysicalAddress;
  UINT16 CurrentEptpIndex;
} VIRTUALIZATION_EXCEPTION_INFORMATION;

/**
 * @}
 */

/**
 * @defgroup VMX_BASIC_EXIT_INFORMATION \
 *           Basic VM-Exit Information
 *
 * Basic VM-Exit Information.
 *
 * @see Vol3C[27.2.1(Basic VM-Exit Information)] (reference)
 * @{
 */
/**
 * @brief Exit Qualification for Debug Exceptions
 */
typedef union
{
  struct
  {
    UINT64 BreakpointCondition                                     : 4;
    UINT64 Reserved1                                               : 9;
    UINT64 DebugRegisterAccessDetected                             : 1;
    UINT64 SingleInstruction                                       : 1;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_DEBUG_EXCEPTION;

/**
 * @brief Exit Qualification for Task Switch
 */
typedef union
{
  struct
  {
    UINT64 Selector                                                : 16;
    UINT64 Reserved1                                               : 14;
    UINT64 Source                                                  : 2;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_TASK_SWITCH;

/**
 * @brief Exit Qualification for Control-Register Accesses
 */
typedef union
{
  struct
  {
    UINT64 ControlRegister                                         : 4;
    UINT64 AccessType                                              : 2;
    UINT64 LmswOperandType                                         : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 GeneralPurposeRegister                                  : 4;
    UINT64 Reserved2                                               : 4;
    UINT64 LmswSourceData                                          : 16;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_MOV_CR;

/**
 * @brief Exit Qualification for MOV DR
 */
typedef union
{
  struct
  {
    UINT64 DebugRegister                                           : 3;
    UINT64 Reserved1                                               : 1;
    UINT64 DirectionOfAccess                                       : 1;
    UINT64 Reserved2                                               : 3;
    UINT64 GeneralPurposeRegister                                  : 4;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_MOV_DR;

/**
 * @brief Exit Qualification for I/O Instructions
 */
typedef union
{
  struct
  {
    UINT64 SizeOfAccess                                            : 3;
    UINT64 DirectionOfAccess                                       : 1;
    UINT64 StringInstruction                                       : 1;
    UINT64 RepPrefixed                                             : 1;
    UINT64 OperandEncoding                                         : 1;
    UINT64 Reserved1                                               : 9;
    UINT64 PortNumber                                              : 16;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_IO_INSTRUCTION;

/**
 * @brief Exit Qualification for APIC-Access VM Exits from Linear Accesses and Guest-Physical Accesses
 */
typedef union
{
  struct
  {
    UINT64 PageOffset                                              : 12;
    UINT64 AccessType                                              : 4;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_APIC_ACCESS;

/**
 * @brief Exit Qualification for EPT Violations
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 EptReadable                                             : 1;
    UINT64 EptWriteable                                            : 1;
    UINT64 EptExecutable                                           : 1;
    UINT64 EptExecutableForUserMode                                : 1;
    UINT64 ValidGuestLinearAddress                                 : 1;
    UINT64 CausedByTranslation                                     : 1;
    UINT64 UserModeLinearAddress                                   : 1;
    UINT64 ReadableWritablePage                                    : 1;
    UINT64 ExecuteDisablePage                                      : 1;
    UINT64 NmiUnblocking                                           : 1;
  };

  UINT64 Flags;
} VMX_EXIT_QUALIFICATION_EPT_VIOLATION;

/**
 * @}
 */

/**
 * @defgroup EPT \
 *           The extended page-table mechanism
 *
 * The extended page-table mechanism (EPT) is a feature that can be used to support the virtualization of physical memory.
 * When EPT is in use, certain addresses that would normally be treated as physical addresses (and used to access memory)
 * are instead treated as guest-physical addresses. Guest-physical addresses are translated by traversing a set of EPT
 * paging structures to produce physical addresses that are used to access memory.
 *
 * @see Vol3C[28.2(THE EXTENDED PAGE TABLE MECHANISM (EPT))] (reference)
 * @{
 */
/**
 * @brief Extended-Page-Table Pointer (EPTP)
 *
 * The extended-page-table pointer (EPTP) contains the address of the base of EPT PML4 table, as well as other EPT
 * configuration information.
 */
typedef union
{
  struct
  {
    UINT64 MemoryType                                              : 3;
    UINT64 PageWalkLength                                          : 3;
    UINT64 EnableAccessAndDirtyFlags                               : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 PageFrameNumber                                         : 36;
  };

  UINT64 Flags;
} EPT_POINTER;

/**
 * @brief Format of an EPT PML4 Entry (PML4E) that References an EPT Page-Directory-Pointer Table
 *
 * A 4-KByte naturally aligned EPT PML4 table is located at the physical address specified in bits 51:12 of the
 * extended-page-table pointer (EPTP), a VM-execution control field. An EPT PML4 table comprises 512 64-bit entries (EPT
 * PML4Es). An EPT PML4E is selected using the physical address defined as follows:
 * - Bits 63:52 are all 0.
 * - Bits 51:12 are from the EPTP.
 * - Bits 11:3 are bits 47:39 of the guest-physical address.
 * - Bits 2:0 are all 0.
 * Because an EPT PML4E is identified using bits 47:39 of the guest-physical address, it controls access to a 512- GByte
 * region of the guest-physical-address space.
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
  };

  UINT64 Flags;
} EPT_PML4;

/**
 * @brief Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 MemoryType                                              : 3;
    UINT64 IgnorePat                                               : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved1                                               : 19;
    UINT64 PageFrameNumber                                         : 18;
    UINT64 Reserved2                                               : 15;
    UINT64 SuppressVe                                              : 1;
  };

  UINT64 Flags;
} EPDPTE_1GB;

/**
 * @brief Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that References an EPT Page Directory
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
  };

  UINT64 Flags;
} EPDPTE;

/**
 * @brief Format of an EPT Page-Directory Entry (PDE) that Maps a 2-MByte Page
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 MemoryType                                              : 3;
    UINT64 IgnorePat                                               : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved1                                               : 10;
    UINT64 PageFrameNumber                                         : 27;
    UINT64 Reserved2                                               : 15;
    UINT64 SuppressVe                                              : 1;
  };

  UINT64 Flags;
} EPDE_2MB;

/**
 * @brief Format of an EPT Page-Directory Entry (PDE) that References an EPT Page Table
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 Reserved1                                               : 5;
    UINT64 Accessed                                                : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved3                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
  };

  UINT64 Flags;
} EPDE;

/**
 * @brief Format of an EPT Page-Table Entry that Maps a 4-KByte Page
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 MemoryType                                              : 3;
    UINT64 IgnorePat                                               : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved2                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved3                                               : 15;
    UINT64 SuppressVe                                              : 1;
  };

  UINT64 Flags;
} EPTE;

/**
 * @brief Format of a common EPT Entry
 */
typedef union
{
  struct
  {
    UINT64 ReadAccess                                              : 1;
    UINT64 WriteAccess                                             : 1;
    UINT64 ExecuteAccess                                           : 1;
    UINT64 MemoryType                                              : 3;
    UINT64 IgnorePat                                               : 1;
    UINT64 LargePage                                               : 1;
    UINT64 Accessed                                                : 1;
    UINT64 Dirty                                                   : 1;
    UINT64 UserModeExecute                                         : 1;
    UINT64 Reserved1                                               : 1;
    UINT64 PageFrameNumber                                         : 36;
    UINT64 Reserved2                                               : 15;
    UINT64 SuppressVe                                              : 1;
  };

  UINT64 Flags;
} EPT_ENTRY;

/**
 * @defgroup EPT_TABLE_LEVEL \
 *           EPT Table level numbers
 *
 * EPT Table level numbers.
 * @{
 */
#define LEVEL_PML4E                                                  0x00000003
#define LEVEL_PDPTE                                                  0x00000002
#define LEVEL_PDE                                                    0x00000001
#define LEVEL_PTE                                                    0x00000000
/**
 * @}
 */

/**
 * @defgroup EPT_ENTRY_COUNT \
 *           EPT Entry counts
 *
 * EPT Entry counts.
 * @{
 */
#define PML4_ENTRY_COUNT                                             0x00000200
#define PDPTE_ENTRY_COUNT                                            0x00000200
#define PDE_ENTRY_COUNT                                              0x00000200
/**
 * @}
 */

/**
 * @defgroup EPT_MEMORY_TYPE \
 *           EPT memory type
 *
 * The effective memory type of a memory access using a guest-physical address (an access that is translated using EPT) is
 * the memory type that is used to access memory. The effective memory type is based on the value of bit 30 (cache
 * disable-CD) in control register CR0; the last EPT paging-structure entry used to translate the guestphysical address
 * (either an EPT PDE with bit 7 set to 1 or an EPT PTE); and the PAT memory type (see below):
 * - The PAT memory type depends on the value of CR0.PG:
 *   * If CR0.PG = 0, the PAT memory type is WB (writeback).
 *   * If CR0.PG = 1, the PAT memory type is the memory type selected from the IA32_PAT MSR.
 * - The EPT memory type is specified in bits 5:3 of the last EPT paging-structure entry: 0 = UC; 1 = WC; 4 = WT; 5 = WP;
 * and 6 = WB. Other values are reserved and cause EPT misconfigurations.
 * - If CR0.CD = 0, the effective memory type depends upon the value of bit 6 of the last EPT paging-structure entry:
 *   * If the value is 0, the effective memory type is the combination of the EPT memory type and the PAT memory type,
 *   using the EPT memory type in place of the MTRR memory type.
 *   * If the value is 1, the memory type used for the access is the EPT memory type. The PAT memory type is ignored.
 * - If CR0.CD = 1, the effective memory type is UC.
 *   The MTRRs have no effect on the memory type used for an access to a guest-physical address.
 *
 * @see MemoryType.yml
 * @see Vol3A[11.5.2.2(Selecting Memory Types for Pentium III and More Recent Processor Families)]
 * @see Vol3A[11.12.3(Selecting a Memory Type from the PAT)]
 * @see Vol3C[28.2.3(EPT-Induced VM Exits)]
 * @see Vol3A[11.11(MEMORY TYPE RANGE REGISTERS (MTRRS))] (reference)
 * @{
 */
#define EPT_MEMORY_TYPE_UNCACHEABLE                                  0x00000000
#define EPT_MEMORY_TYPE_WRITE_COMBINING                              0x00000001
#define EPT_MEMORY_TYPE_WRITE_THROUGH                                0x00000004
#define EPT_MEMORY_TYPE_WRITE_PROTECTED                              0x00000005
#define EPT_MEMORY_TYPE_WRITE_BACK                                   0x00000006
#define EPT_MEMORY_TYPE_UNCACHED                                     0x00000007
#define EPT_MEMORY_TYPE_INVALID                                      0x000000FF
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS \
 *           VMCS (VM Control Structure)
 *
 * Every component of the VMCS is encoded by a 32-bit field that can be used by VMREAD and VMWRITE. This enumerates all
 * fields in the VMCS and their encodings. Fields are grouped by width (16-bit, 32-bit, etc.) and type (guest-state,
 * host-state, etc.).
 *
 * @see Vol3D[B(APPENDIX B FIELD ENCODING IN VMCS)] (reference)
 * @{
 */
typedef union
{
  struct
  {
    UINT16 AccessType                                              : 1;
    UINT16 Index                                                   : 9;
    UINT16 Type                                                    : 2;
    UINT16 MustBeZero                                              : 1;
    UINT16 Width                                                   : 2;
  };

  UINT16 Flags;
} VMCS_COMPONENT_ENCODING;

/**
 * @defgroup VMCS_16_BIT \
 *           16-Bit Fields
 *
 * 16-Bit Fields.
 *
 * @see Vol3D[B.1(16-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_16_BIT_CONTROL_FIELDS \
 *           16-Bit Control Fields
 *
 * 16-Bit Control Fields.
 * @{
 */
/**
 * @brief Virtual-processor identifier (VPID).
 */
#define VMCS_CTRL_VIRTUAL_PROCESSOR_IDENTIFIER                       0x00000000

/**
 * @brief Posted-interrupt notification vector.
 */
#define VMCS_CTRL_POSTED_INTERRUPT_NOTIFICATION_VECTOR               0x00000002

/**
 * @brief EPTP index.
 */
#define VMCS_CTRL_EPTP_INDEX                                         0x00000004

/**
 * @}
 */

/**
 * @defgroup VMCS_16_BIT_GUEST_STATE_FIELDS \
 *           16-Bit Guest-State Fields
 *
 * 16-Bit Guest-State Fields.
 * @{
 */
/**
 * @brief Guest ES selector.
 */
#define VMCS_GUEST_ES_SELECTOR                                       0x00000800

/**
 * @brief Guest CS selector.
 */
#define VMCS_GUEST_CS_SELECTOR                                       0x00000802

/**
 * @brief Guest SS selector.
 */
#define VMCS_GUEST_SS_SELECTOR                                       0x00000804

/**
 * @brief Guest DS selector.
 */
#define VMCS_GUEST_DS_SELECTOR                                       0x00000806

/**
 * @brief Guest FS selector.
 */
#define VMCS_GUEST_FS_SELECTOR                                       0x00000808

/**
 * @brief Guest GS selector.
 */
#define VMCS_GUEST_GS_SELECTOR                                       0x0000080A

/**
 * @brief Guest LDTR selector.
 */
#define VMCS_GUEST_LDTR_SELECTOR                                     0x0000080C

/**
 * @brief Guest TR selector.
 */
#define VMCS_GUEST_TR_SELECTOR                                       0x0000080E

/**
 * @brief Guest interrupt status.
 */
#define VMCS_GUEST_INTERRUPT_STATUS                                  0x00000810

/**
 * @brief PML index.
 */
#define VMCS_GUEST_PML_INDEX                                         0x00000812

/**
 * @}
 */

/**
 * @defgroup VMCS_16_BIT_HOST_STATE_FIELDS \
 *           16-Bit Host-State Fields
 *
 * 16-Bit Host-State Fields.
 * @{
 */
/**
 * @brief Host ES selector.
 */
#define VMCS_HOST_ES_SELECTOR                                        0x00000C00

/**
 * @brief Host CS selector.
 */
#define VMCS_HOST_CS_SELECTOR                                        0x00000C02

/**
 * @brief Host SS selector.
 */
#define VMCS_HOST_SS_SELECTOR                                        0x00000C04

/**
 * @brief Host DS selector.
 */
#define VMCS_HOST_DS_SELECTOR                                        0x00000C06

/**
 * @brief Host FS selector.
 */
#define VMCS_HOST_FS_SELECTOR                                        0x00000C08

/**
 * @brief Host GS selector.
 */
#define VMCS_HOST_GS_SELECTOR                                        0x00000C0A

/**
 * @brief Host TR selector.
 */
#define VMCS_HOST_TR_SELECTOR                                        0x00000C0C

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT \
 *           64-Bit Fields
 *
 * 64-Bit Fields.
 *
 * @see Vol3D[B.2(64-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_64_BIT_CONTROL_FIELDS \
 *           64-Bit Control Fields
 *
 * 64-Bit Control Fields.
 * @{
 */
/**
 * @brief Address of I/O bitmap A.
 */
#define VMCS_CTRL_IO_BITMAP_A_ADDRESS                                0x00002000

/**
 * @brief Address of I/O bitmap B.
 */
#define VMCS_CTRL_IO_BITMAP_B_ADDRESS                                0x00002002

/**
 * @brief Address of MSR bitmaps.
 */
#define VMCS_CTRL_MSR_BITMAP_ADDRESS                                 0x00002004

/**
 * @brief VM-exit MSR-store address.
 */
#define VMCS_CTRL_VMEXIT_MSR_STORE_ADDRESS                           0x00002006

/**
 * @brief VM-exit MSR-load address.
 */
#define VMCS_CTRL_VMEXIT_MSR_LOAD_ADDRESS                            0x00002008

/**
 * @brief VM-entry MSR-load address.
 */
#define VMCS_CTRL_VMENTRY_MSR_LOAD_ADDRESS                           0x0000200A

/**
 * @brief Executive-VMCS pointer.
 */
#define VMCS_CTRL_EXECUTIVE_VMCS_POINTER                             0x0000200C

/**
 * @brief PML address.
 */
#define VMCS_CTRL_PML_ADDRESS                                        0x0000200E

/**
 * @brief TSC offset.
 */
#define VMCS_CTRL_TSC_OFFSET                                         0x00002010

/**
 * @brief Virtual-APIC address.
 */
#define VMCS_CTRL_VIRTUAL_APIC_ADDRESS                               0x00002012

/**
 * @brief APIC-access address.
 */
#define VMCS_CTRL_APIC_ACCESS_ADDRESS                                0x00002014

/**
 * @brief Posted-interrupt descriptor address
 */
#define VMCS_CTRL_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS                0x00002016

/**
 * @brief VM-function controls.
 */
#define VMCS_CTRL_VMFUNC_CONTROLS                                    0x00002018

/**
 * @brief EPT pointer.
 */
#define VMCS_CTRL_EPT_POINTER                                        0x0000201A

/**
 * @brief EOI-exit bitmap 0.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_0                                  0x0000201C

/**
 * @brief EOI-exit bitmap 1.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_1                                  0x0000201E

/**
 * @brief EOI-exit bitmap 2.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_2                                  0x00002020

/**
 * @brief EOI-exit bitmap 3.
 */
#define VMCS_CTRL_EOI_EXIT_BITMAP_3                                  0x00002022

/**
 * @brief EPTP-list address.
 */
#define VMCS_CTRL_EPT_POINTER_LIST_ADDRESS                           0x00002024

/**
 * @brief VMREAD-bitmap address.
 */
#define VMCS_CTRL_VMREAD_BITMAP_ADDRESS                              0x00002026

/**
 * @brief VMWRITE-bitmap address.
 */
#define VMCS_CTRL_VMWRITE_BITMAP_ADDRESS                             0x00002028

/**
 * @brief Virtualization-exception information address.
 */
#define VMCS_CTRL_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS       0x0000202A

/**
 * @brief XSS-exiting bitmap.
 */
#define VMCS_CTRL_XSS_EXITING_BITMAP                                 0x0000202C

/**
 * @brief ENCLS-exiting bitmap.
 */
#define VMCS_CTRL_ENCLS_EXITING_BITMAP                               0x0000202E

/**
 * @brief TSC multiplier.
 */
#define VMCS_CTRL_TSC_MULTIPLIER                                     0x00002032

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_READ_ONLY_DATA_FIELDS \
 *           64-Bit Read-Only Data Field
 *
 * 64-Bit Read-Only Data Field.
 * @{
 */
/**
 * @brief Guest-physical address.
 */
#define VMCS_GUEST_PHYSICAL_ADDRESS                                  0x00002400

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_GUEST_STATE_FIELDS \
 *           64-Bit Guest-State Fields
 *
 * 64-Bit Guest-State Fields.
 * @{
 */
/**
 * @brief VMCS link pointer.
 */
#define VMCS_GUEST_VMCS_LINK_POINTER                                 0x00002800

/**
 * @brief Guest IA32_DEBUGCTL.
 */
#define VMCS_GUEST_DEBUGCTL                                          0x00002802

/**
 * @brief Guest IA32_PAT.
 */
#define VMCS_GUEST_PAT                                               0x00002804

/**
 * @brief Guest IA32_EFER.
 */
#define VMCS_GUEST_EFER                                              0x00002806

/**
 * @brief Guest IA32_PERF_GLOBAL_CTRL.
 */
#define VMCS_GUEST_PERF_GLOBAL_CTRL                                  0x00002808

/**
 * @brief Guest PDPTE0.
 */
#define VMCS_GUEST_PDPTE0                                            0x0000280A

/**
 * @brief Guest PDPTE1.
 */
#define VMCS_GUEST_PDPTE1                                            0x0000280C

/**
 * @brief Guest PDPTE2.
 */
#define VMCS_GUEST_PDPTE2                                            0x0000280E

/**
 * @brief Guest PDPTE3.
 */
#define VMCS_GUEST_PDPTE3                                            0x00002810

/**
 * @}
 */

/**
 * @defgroup VMCS_64_BIT_HOST_STATE_FIELDS \
 *           64-Bit Host-State Fields
 *
 * 64-Bit Host-State Fields.
 * @{
 */
/**
 * @brief Host IA32_PAT.
 */
#define VMCS_HOST_PAT                                                0x00002C00

/**
 * @brief Host IA32_EFER.
 */
#define VMCS_HOST_EFER                                               0x00002C02

/**
 * @brief Host IA32_PERF_GLOBAL_CTRL.
 */
#define VMCS_HOST_PERF_GLOBAL_CTRL                                   0x00002C04

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT \
 *           32-Bit Fields
 *
 * 32-Bit Fields.
 *
 * @see Vol3D[B.3(32-BIT FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_32_BIT_CONTROL_FIELDS \
 *           32-Bit Control Fields
 *
 * 32-Bit Control Fields.
 * @{
 */
/**
 * @brief Pin-based VM-execution controls.
 */
#define VMCS_CTRL_PIN_BASED_VM_EXECUTION_CONTROLS                    0x00004000

/**
 * @brief Primary processor-based VM-execution controls.
 */
#define VMCS_CTRL_PROCESSOR_BASED_VM_EXECUTION_CONTROLS              0x00004002

/**
 * @brief Exception bitmap.
 */
#define VMCS_CTRL_EXCEPTION_BITMAP                                   0x00004004

/**
 * @brief Page-fault error-code mask.
 */
#define VMCS_CTRL_PAGEFAULT_ERROR_CODE_MASK                          0x00004006

/**
 * @brief Page-fault error-code match.
 */
#define VMCS_CTRL_PAGEFAULT_ERROR_CODE_MATCH                         0x00004008

/**
 * @brief CR3-target count.
 */
#define VMCS_CTRL_CR3_TARGET_COUNT                                   0x0000400A

/**
 * @brief VM-exit controls.
 */
#define VMCS_CTRL_VMEXIT_CONTROLS                                    0x0000400C

/**
 * @brief VM-exit MSR-store count.
 */
#define VMCS_CTRL_VMEXIT_MSR_STORE_COUNT                             0x0000400E

/**
 * @brief VM-exit MSR-load count.
 */
#define VMCS_CTRL_VMEXIT_MSR_LOAD_COUNT                              0x00004010

/**
 * @brief VM-entry controls.
 */
#define VMCS_CTRL_VMENTRY_CONTROLS                                   0x00004012

/**
 * @brief VM-entry MSR-load count.
 */
#define VMCS_CTRL_VMENTRY_MSR_LOAD_COUNT                             0x00004014

/**
 * @brief VM-entry interruption-information field.
 */
#define VMCS_CTRL_VMENTRY_INTERRUPTION_INFORMATION_FIELD             0x00004016

/**
 * @brief VM-entry exception error code.
 */
#define VMCS_CTRL_VMENTRY_EXCEPTION_ERROR_CODE                       0x00004018

/**
 * @brief VM-entry instruction length.
 */
#define VMCS_CTRL_VMENTRY_INSTRUCTION_LENGTH                         0x0000401A

/**
 * @brief TPR threshold.
 */
#define VMCS_CTRL_TPR_THRESHOLD                                      0x0000401C

/**
 * @brief Secondary processor-based VM-execution controls.
 */
#define VMCS_CTRL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS    0x0000401E

/**
 * @brief PLE_Gap.
 */
#define VMCS_CTRL_PLE_GAP                                            0x00004020

/**
 * @brief PLE_Window.
 */
#define VMCS_CTRL_PLE_WINDOW                                         0x00004022

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_READ_ONLY_DATA_FIELDS \
 *           32-Bit Read-Only Data Fields
 *
 * 32-Bit Read-Only Data Fields.
 * @{
 */
/**
 * @brief VM-instruction error.
 */
#define VMCS_VM_INSTRUCTION_ERROR                                    0x00004400

/**
 * @brief Exit reason.
 */
#define VMCS_EXIT_REASON                                             0x00004402

/**
 * @brief VM-exit interruption information.
 */
#define VMCS_VMEXIT_INTERRUPTION_INFORMATION                         0x00004404

/**
 * @brief VM-exit interruption error code.
 */
#define VMCS_VMEXIT_INTERRUPTION_ERROR_CODE                          0x00004406

/**
 * @brief IDT-vectoring information field.
 */
#define VMCS_IDT_VECTORING_INFORMATION                               0x00004408

/**
 * @brief IDT-vectoring error code.
 */
#define VMCS_IDT_VECTORING_ERROR_CODE                                0x0000440A

/**
 * @brief VM-exit instruction length.
 */
#define VMCS_VMEXIT_INSTRUCTION_LENGTH                               0x0000440C

/**
 * @brief VM-exit instruction information.
 */
#define VMCS_VMEXIT_INSTRUCTION_INFO                                 0x0000440E

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_GUEST_STATE_FIELDS \
 *           32-Bit Guest-State Fields
 *
 * 32-Bit Guest-State Fields.
 * @{
 */
/**
 * @brief Guest ES limit.
 */
#define VMCS_GUEST_ES_LIMIT                                          0x00004800

/**
 * @brief Guest CS limit.
 */
#define VMCS_GUEST_CS_LIMIT                                          0x00004802

/**
 * @brief Guest SS limit.
 */
#define VMCS_GUEST_SS_LIMIT                                          0x00004804

/**
 * @brief Guest DS limit.
 */
#define VMCS_GUEST_DS_LIMIT                                          0x00004806

/**
 * @brief Guest FS limit.
 */
#define VMCS_GUEST_FS_LIMIT                                          0x00004808

/**
 * @brief Guest GS limit.
 */
#define VMCS_GUEST_GS_LIMIT                                          0x0000480A

/**
 * @brief Guest LDTR limit.
 */
#define VMCS_GUEST_LDTR_LIMIT                                        0x0000480C

/**
 * @brief Guest TR limit.
 */
#define VMCS_GUEST_TR_LIMIT                                          0x0000480E

/**
 * @brief Guest GDTR limit.
 */
#define VMCS_GUEST_GDTR_LIMIT                                        0x00004810

/**
 * @brief Guest IDTR limit.
 */
#define VMCS_GUEST_IDTR_LIMIT                                        0x00004812

/**
 * @brief Guest ES access rights.
 */
#define VMCS_GUEST_ES_ACCESS_RIGHTS                                  0x00004814

/**
 * @brief Guest CS access rights.
 */
#define VMCS_GUEST_CS_ACCESS_RIGHTS                                  0x00004816

/**
 * @brief Guest SS access rights.
 */
#define VMCS_GUEST_SS_ACCESS_RIGHTS                                  0x00004818

/**
 * @brief Guest DS access rights.
 */
#define VMCS_GUEST_DS_ACCESS_RIGHTS                                  0x0000481A

/**
 * @brief Guest FS access rights.
 */
#define VMCS_GUEST_FS_ACCESS_RIGHTS                                  0x0000481C

/**
 * @brief Guest GS access rights.
 */
#define VMCS_GUEST_GS_ACCESS_RIGHTS                                  0x0000481E

/**
 * @brief Guest LDTR access rights.
 */
#define VMCS_GUEST_LDTR_ACCESS_RIGHTS                                0x00004820

/**
 * @brief Guest TR access rights.
 */
#define VMCS_GUEST_TR_ACCESS_RIGHTS                                  0x00004822

/**
 * @brief Guest interruptibility state.
 */
#define VMCS_GUEST_INTERRUPTIBILITY_STATE                            0x00004824

/**
 * @brief Guest activity state.
 */
#define VMCS_GUEST_ACTIVITY_STATE                                    0x00004826

/**
 * @brief Guest SMBASE.
 */
#define VMCS_GUEST_SMBASE                                            0x00004828

/**
 * @brief Guest IA32_SYSENTER_CS.
 */
#define VMCS_GUEST_SYSENTER_CS                                       0x0000482A

/**
 * @brief VMX-preemption timer value.
 */
#define VMCS_GUEST_VMX_PREEMPTION_TIMER_VALUE                        0x0000482E

/**
 * @}
 */

/**
 * @defgroup VMCS_32_BIT_HOST_STATE_FIELDS \
 *           32-Bit Host-State Field
 *
 * 32-Bit Host-State Field.
 * @{
 */
/**
 * @brief Host IA32_SYSENTER_CS.
 */
#define VMCS_SYSENTER_CS                                             0x00004C00

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH \
 *           Natural-Width Fields
 *
 * Natural-Width Fields.
 *
 * @see Vol3D[B.4(NATURAL-WIDTH FIELDS)] (reference)
 * @{
 */
/**
 * @defgroup VMCS_NATURAL_WIDTH_CONTROL_FIELDS \
 *           Natural-Width Control Fields
 *
 * Natural-Width Control Fields
 * @{
 */
/**
 * @brief CR0 guest/host mask.
 */
#define VMCS_CTRL_CR0_GUEST_HOST_MASK                                0x00006000

/**
 * @brief CR4 guest/host mask.
 */
#define VMCS_CTRL_CR4_GUEST_HOST_MASK                                0x00006002

/**
 * @brief CR0 read shadow.
 */
#define VMCS_CTRL_CR0_READ_SHADOW                                    0x00006004

/**
 * @brief CR4 read shadow.
 */
#define VMCS_CTRL_CR4_READ_SHADOW                                    0x00006006

/**
 * @brief CR3-target value 0.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_0                                 0x00006008

/**
 * @brief CR3-target value 1.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_1                                 0x0000600A

/**
 * @brief CR3-target value 2.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_2                                 0x0000600C

/**
 * @brief CR3-target value 3.
 */
#define VMCS_CTRL_CR3_TARGET_VALUE_3                                 0x0000600E

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_READ_ONLY_DATA_FIELDS \
 *           Natural-Width Read-Only Data Fields
 *
 * Natural-Width Read-Only Data Fields.
 * @{
 */
/**
 * @brief Exit qualification.
 */
#define VMCS_EXIT_QUALIFICATION                                      0x00006400

/**
 * @brief I/O RCX.
 */
#define VMCS_IO_RCX                                                  0x00006402

/**
 * @brief I/O RSI.
 */
#define VMCS_IO_RSX                                                  0x00006404

/**
 * @brief I/O RDI.
 */
#define VMCS_IO_RDI                                                  0x00006406

/**
 * @brief I/O RIP.
 */
#define VMCS_IO_RIP                                                  0x00006408

/**
 * @brief Guest-linear address.
 */
#define VMCS_EXIT_GUEST_LINEAR_ADDRESS                               0x0000640A

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_GUEST_STATE_FIELDS \
 *           Natural-Width Guest-State Fields
 *
 * Natural-Width Guest-State Fields.
 * @{
 */
/**
 * @brief Guest CR0.
 */
#define VMCS_GUEST_CR0                                               0x00006800

/**
 * @brief Guest CR3.
 */
#define VMCS_GUEST_CR3                                               0x00006802

/**
 * @brief Guest CR4.
 */
#define VMCS_GUEST_CR4                                               0x00006804

/**
 * @brief Guest ES base.
 */
#define VMCS_GUEST_ES_BASE                                           0x00006806

/**
 * @brief Guest CS base.
 */
#define VMCS_GUEST_CS_BASE                                           0x00006808

/**
 * @brief Guest SS base.
 */
#define VMCS_GUEST_SS_BASE                                           0x0000680A

/**
 * @brief Guest DS base.
 */
#define VMCS_GUEST_DS_BASE                                           0x0000680C

/**
 * @brief Guest FS base.
 */
#define VMCS_GUEST_FS_BASE                                           0x0000680E

/**
 * @brief Guest GS base.
 */
#define VMCS_GUEST_GS_BASE                                           0x00006810

/**
 * @brief Guest LDTR base.
 */
#define VMCS_GUEST_LDTR_BASE                                         0x00006812

/**
 * @brief Guest TR base.
 */
#define VMCS_GUEST_TR_BASE                                           0x00006814

/**
 * @brief Guest GDTR base.
 */
#define VMCS_GUEST_GDTR_BASE                                         0x00006816

/**
 * @brief Guest IDTR base.
 */
#define VMCS_GUEST_IDTR_BASE                                         0x00006818

/**
 * @brief Guest DR7.
 */
#define VMCS_GUEST_DR7                                               0x0000681A

/**
 * @brief Guest RSP.
 */
#define VMCS_GUEST_RSP                                               0x0000681C

/**
 * @brief Guest RIP.
 */
#define VMCS_GUEST_RIP                                               0x0000681E

/**
 * @brief Guest RFLAGS.
 */
#define VMCS_GUEST_RFLAGS                                            0x00006820

/**
 * @brief Guest pending debug exceptions.
 */
#define VMCS_GUEST_PENDING_DEBUG_EXCEPTIONS                          0x00006822

/**
 * @brief Guest IA32_SYSENTER_ESP.
 */
#define VMCS_GUEST_SYSENTER_ESP                                      0x00006824

/**
 * @brief Guest IA32_SYSENTER_EIP.
 */
#define VMCS_GUEST_SYSENTER_EIP                                      0x00006826

/**
 * @}
 */

/**
 * @defgroup VMCS_NATURAL_WIDTH_HOST_STATE_FIELDS \
 *           Natural-Width Host-State Fields
 *
 * Natural-Width Host-State Fields.
 * @{
 */
/**
 * @brief Host CR0.
 */
#define VMCS_HOST_CR0                                                0x00006C00

/**
 * @brief Host CR3.
 */
#define VMCS_HOST_CR3                                                0x00006C02

/**
 * @brief Host CR4.
 */
#define VMCS_HOST_CR4                                                0x00006C04

/**
 * @brief Host FS base.
 */
#define VMCS_HOST_FS_BASE                                            0x00006C06

/**
 * @brief Host GS base.
 */
#define VMCS_HOST_GS_BASE                                            0x00006C08

/**
 * @brief Host TR base.
 */
#define VMCS_HOST_TR_BASE                                            0x00006C0A

/**
 * @brief Host GDTR base.
 */
#define VMCS_HOST_GDTR_BASE                                          0x00006C0C

/**
 * @brief Host IDTR base.
 */
#define VMCS_HOST_IDTR_BASE                                          0x00006C0E

/**
 * @brief Host IA32_SYSENTER_ESP.
 */
#define VMCS_HOST_SYSENTER_ESP                                       0x00006C10

/**
 * @brief Host IA32_SYSENTER_EIP.
 */
#define VMCS_HOST_SYSENTER_EIP                                       0x00006C12

/**
 * @brief Host RSP.
 */
#define VMCS_HOST_RSP                                                0x00006C14

/**
 * @brief Host RIP.
 */
#define VMCS_HOST_RIP                                                0x00006C16

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup APIC \
 *           Advanced Programmable Interrupt Controller (APIC)
 *
 * Software interacts with the local APIC by reading and writing its registers. APIC registers are memory-mapped to a
 * 4-KByte region of the processor's physical address space with an initial starting address of FEE00000H. For correct APIC
 * operation, this address space must be mapped to an area of memory that has been designated as strong uncacheable (UC).
 *
 * @remarks Registers are 32 bits, 64 bits, or 256 bits in width; all are aligned on 128-bit boundaries. All 32-bit
 *          registers should be accessed using 128-bit aligned 32-bit loads or stores. Some processors may support loads and stores
 *          of less than 32 bits to some of the APIC registers. This is model specific behavior and is not guaranteed to work on all
 *          processors. Any FP/MMX/SSE access to an APIC register, or any access that touches bytes 4 through 15 of an APIC register
 *          may cause undefined behavior and must not be executed. This undefined behavior could include hangs, incorrect results or
 *          unexpected exceptions, including machine checks, and may vary between implementations. Wider registers (64-bit or
 *          256-bit) must be accessed using multiple 32-bit loads or stores, with all accesses being 128-bit aligned.
 * @see Vol3A[10.4.1(The Local APIC Block Diagram)] (reference)
 * @{
 */
/**
 * @brief Local APIC Base Address.
 */
#define APIC_BASE_ADDRESS                                            0xFEE00000

/**
 * @brief Local APIC ID Register. <b>(Read/Write)</b>
 */
#define APIC_ID                                                      0xFEE00020

/**
 * @brief Local APIC Version Register. <b>(Read Only)</b>
 */
#define APIC_VERSION                                                 0xFEE00030

/**
 * @brief Task Priority Register (TPR). <b>(Read/Write)</b>
 */
#define APIC_TASK_PRIORITY                                           0xFEE00080

/**
 * @brief Arbitration Priority Register (APR). <b>(Read Only)</b>
 */
#define APIC_ARBITRATION_PRIORITY                                    0xFEE00090

/**
 * @brief Processor Priority Register (PPR). <b>(Read Only)</b>
 */
#define APIC_PROCESSOR_PRIORITY                                      0xFEE000A0

/**
 * @brief EOI Register. <b>(Write Only)</b>
 */
#define APIC_EOI                                                     0xFEE000B0

/**
 * @brief Remote Read Register (RRD). <b>(Read Only)</b>
 */
#define APIC_REMOTE_READ                                             0xFEE000C0

/**
 * @brief Logical Destination Register. <b>(Read/Write)</b>
 */
#define APIC_LOGICAL_DESTINATION                                     0xFEE000D0

/**
 * @brief Destination Format Register. <b>(Read/Write)</b>
 */
#define APIC_DESTINATION_FORMAT                                      0xFEE000E0

/**
 * @brief Spurious Interrupt Vector Register. <b>(Read/Write)</b>
 */
#define APIC_SPURIOUS_INTERRUPT_VECTOR                               0xFEE000F0

/**
 * @brief In-Service Register (ISR); bits 31:0. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_31_0                                    0xFEE00100

/**
 * @brief In-Service Register (ISR); bits 63:32. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_63_32                                   0xFEE00110

/**
 * @brief In-Service Register (ISR); bits 95:64. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_95_64                                   0xFEE00120

/**
 * @brief In-Service Register (ISR); bits 127:96. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_127_96                                  0xFEE00130

/**
 * @brief In-Service Register (ISR); bits 159:128. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_159_128                                 0xFEE00140

/**
 * @brief In-Service Register (ISR); bits 191:160. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_191_160                                 0xFEE00150

/**
 * @brief In-Service Register (ISR); bits 223:192. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_223_192                                 0xFEE00160

/**
 * @brief In-Service Register (ISR); bits 255:224. <b>(Read Only)</b>
 */
#define APIC_IN_SERVICE_BITS_255_224                                 0xFEE00170

/**
 * @brief Trigger Mode Register (TMR); bits 31:0. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_31_0                                  0xFEE00180

/**
 * @brief Trigger Mode Register (TMR); bits 63:32. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_63_32                                 0xFEE00190

/**
 * @brief Trigger Mode Register (TMR); bits 95:64. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_95_64                                 0xFEE001A0

/**
 * @brief Trigger Mode Register (TMR); bits 127:96. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_127_96                                0xFEE001B0

/**
 * @brief Trigger Mode Register (TMR); bits 159:128. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_159_128                               0xFEE001C0

/**
 * @brief Trigger Mode Register (TMR); bits 191:160. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_191_160                               0xFEE001D0

/**
 * @brief Trigger Mode Register (TMR); bits 223:192. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_223_192                               0xFEE001E0

/**
 * @brief Trigger Mode Register (TMR); bits 255:224. <b>(Read Only)</b>
 */
#define APIC_TRIGGER_MODE_BITS_255_224                               0xFEE001F0

/**
 * @brief Interrupt Request Register (IRR); bits 31:0. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_31_0                             0xFEE00200

/**
 * @brief Interrupt Request Register (IRR); bits 63:32. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_63_32                            0xFEE00210

/**
 * @brief Interrupt Request Register (IRR); bits 95:64. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_95_64                            0xFEE00220

/**
 * @brief Interrupt Request Register (IRR); bits 127:96. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_127_96                           0xFEE00230

/**
 * @brief Interrupt Request Register (IRR); bits 159:128. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_159_128                          0xFEE00240

/**
 * @brief Interrupt Request Register (IRR); bits 191:160. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_191_160                          0xFEE00250

/**
 * @brief Interrupt Request Register (IRR); bits 223:192. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_223_192                          0xFEE00260

/**
 * @brief Interrupt Request Register (IRR); bits 255:224. <b>(Read Only)</b>
 */
#define APIC_INTERRUPT_REQUEST_BITS_255_224                          0xFEE00270

/**
 * @brief Error Status Register. <b>(Read Only)</b>
 */
#define APIC_ERROR_STATUS                                            0xFEE00280

/**
 * @brief LVT Corrected Machine Check Interrupt (CMCI) Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_CORRECTED_MACHINE_CHECK_INTERRUPT                   0xFEE002F0

/**
 * @brief Interrupt Command Register (ICR); bits 0-31. <b>(Read/Write)</b>
 */
#define APIC_INTERRUPT_COMMAND_BITS_0_31                             0xFEE00300

/**
 * @brief Interrupt Command Register (ICR); bits 32-63. <b>(Read/Write)</b>
 */
#define APIC_INTERRUPT_COMMAND_BITS_32_63                            0xFEE00310

/**
 * @brief LVT Timer Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_TIMER                                               0xFEE00320

/**
 * @brief LVT Thermal Sensor Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_THERMAL_SENSOR                                      0xFEE00330

/**
 * @brief LVT Performance Monitoring Counters Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_PERFORMANCE_MONITORING_COUNTERS                     0xFEE00340

/**
 * @brief LVT LINT0 Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_LINT0                                               0xFEE00350

/**
 * @brief LVT LINT1 Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_LINT1                                               0xFEE00360

/**
 * @brief LVT Error Register. <b>(Read/Write)</b>
 */
#define APIC_LVT_ERROR                                               0xFEE00370

/**
 * @brief Initial Count Register (for Timer). <b>(Read/Write)</b>
 */
#define APIC_INITIAL_COUNT                                           0xFEE00380

/**
 * @brief Current Count Register (for Timer). <b>(Read Only)</b>
 */
#define APIC_CURRENT_COUNT                                           0xFEE00390

/**
 * @brief Divide Configuration Register (for Timer). <b>(Read/Write)</b>
 */
#define APIC_DIVIDE_CONFIGURATION                                    0xFEE003E0

/**
 * @}
 */

typedef union
{
  struct
  {
    UINT32 CarryFlag                                               : 1;
    UINT32 ReadAs1                                                 : 1;
    UINT32 ParityFlag                                              : 1;
    UINT32 Reserved1                                               : 1;
    UINT32 AuxiliaryCarryFlag                                      : 1;
    UINT32 Reserved2                                               : 1;
    UINT32 ZeroFlag                                                : 1;
    UINT32 SignFlag                                                : 1;
    UINT32 TrapFlag                                                : 1;
    UINT32 InterruptEnableFlag                                     : 1;
    UINT32 DirectionFlag                                           : 1;
    UINT32 OverflowFlag                                            : 1;
    UINT32 IoPrivilegeLevel                                        : 2;
    UINT32 NestedTaskFlag                                          : 1;
    UINT32 Reserved3                                               : 1;
    UINT32 ResumeFlag                                              : 1;
    UINT32 Virtual8086ModeFlag                                     : 1;
    UINT32 AlignmentCheckFlag                                      : 1;
    UINT32 VirtualInterruptFlag                                    : 1;
    UINT32 VirtualInterruptPendingFlag                             : 1;
    UINT32 IdentificationFlag                                      : 1;
  };

  UINT32 Flags;
} EFLAGS;

/**
 * @defgroup MEMORY_TYPE \
 *           Memory caching type
 *
 * The processor allows any area of system memory to be cached in the L1, L2, and L3 caches. In individual pages or regions
 * of system memory, it allows the type of caching (also called memory type) to be specified.
 *
 * @see Vol3A[11.11(MEMORY TYPE RANGE REGISTERS (MTRRS))]
 * @see Vol3A[11.5(CACHE CONTROL)]
 * @see Vol3A[11.3(METHODS OF CACHING AVAILABLE)] (reference)
 * @{
 */
/**
 * @brief System memory locations are not cached. All reads and writes appear on the system bus and are executed in program
 *        order without reordering. No speculative memory accesses, pagetable walks, or prefetches of speculated branch targets
 *        are made. This type of cache-control is useful for memory-mapped I/O devices. When used with normal RAM, it greatly
 *        reduces processor performance.
 */
#define MEMORY_TYPE_UNCACHEABLE                                      0x00000000

/**
 * @brief System memory locations are not cached (as with uncacheable memory) and coherency is not enforced by the
 *        processor's bus coherency protocol. Speculative reads are allowed. Writes may be delayed and combined in the write
 *        combining buffer (WC buffer) to reduce memory accesses. If the WC buffer is partially filled, the writes may be delayed
 *        until the next occurrence of a serializing event; such as, an SFENCE or MFENCE instruction, CPUID execution, a read or
 *        write to uncached memory, an interrupt occurrence, or a LOCK instruction execution. This type of cache-control is
 *        appropriate for video frame buffers, where the order of writes is unimportant as long as the writes update memory so
 *        they can be seen on the graphics display. This memory type is available in the Pentium Pro and Pentium II processors by
 *        programming the MTRRs; or in processor families starting from the Pentium III processors by programming the MTRRs or by
 *        selecting it through the PAT.
 */
#define MEMORY_TYPE_WRITE_COMBINING                                  0x00000001

/**
 * @brief Writes and reads to and from system memory are cached. Reads come from cache lines on cache hits; read misses
 *        cause cache fills. Speculative reads are allowed. All writes are written to a cache line (when possible) and through to
 *        system memory. When writing through to memory, invalid cache lines are never filled, and valid cache lines are either
 *        filled or invalidated. Write combining is allowed. This type of cache-control is appropriate for frame buffers or when
 *        there are devices on the system bus that access system memory, but do not perform snooping of memory accesses. It
 *        enforces coherency between caches in the processors and system memory.
 */
#define MEMORY_TYPE_WRITE_THROUGH                                    0x00000004

#define MEMORY_TYPE_WRITE_PROTECTED                                  0x00000005
/**
 * @brief Reads come from cache lines when possible, and read misses cause cache fills. Writes are propagated to the system
 *        bus and cause corresponding cache lines on all processors on the bus to be invalidated. Speculative reads are allowed.
 *        This memory type is available in processor families starting from the P6 family processors by programming the MTRRs.
 */
#define MEMORY_TYPE_WRITE_BACK                                       0x00000006

#define MEMORY_TYPE_UNCACHED                                         0x00000007
#define MEMORY_TYPE_INVALID                                          0x000000FF
/**
 * @}
 */

/**
 * @}
 */

