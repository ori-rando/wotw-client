#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::IBrainControllerExtensions {
    IL2CPP_REGISTER_METHOD(0x01BAA500, int32_t, ToInt, (app::Enum e))
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_1, (app::IBrainController_1_BrainEntityTester_BrainTesterEntries_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x047130E8, IBrainControllerExtensions_BuildEntries__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_2, (app::IBrainController_1_ConditionBasedBrainController_BranchingBoolEntries_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x0471E820, IBrainControllerExtensions_BuildEntries_1__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_3, (app::IBrainController_1_InWaterMode_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04748898, IBrainControllerExtensions_BuildEntries_2__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_4, (app::IBrainController_1_KwolokBossEntity_AnimationDirections_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04742328, IBrainControllerExtensions_BuildEntries_3__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_5, (app::IBrainController_1_KwolokBossTendril_DurationType_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x047659F0, IBrainControllerExtensions_BuildEntries_4__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_6, (app::IBrainController_1_KwolokBossTendril_VariationType_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x0476F590, IBrainControllerExtensions_BuildEntries_5__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_7, (app::IBrainController_1_TentacleStabOutcome_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04796778, IBrainControllerExtensions_BuildEntries_6__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_8, (app::IBrainController_1_NightCrawlerBackAttackBranches_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04771010, IBrainControllerExtensions_BuildEntries_7__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_9, (app::IBrainController_1_NightCrawlerChaseIntroBranches_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04713E48, IBrainControllerExtensions_BuildEntries_8__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_10, (app::IBrainController_1_NightCrawlerRetaliationBranches_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04761DC0, IBrainControllerExtensions_BuildEntries_9__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_11, (app::IBrainController_1_PetrifiedOwlBossEntity_AnimationDirections_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x0471E230, IBrainControllerExtensions_BuildEntries_10__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_12, (app::IBrainController_1_SpiderBossAnimationDirection_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x0475FBF0, IBrainControllerExtensions_BuildEntries_11__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_13, (app::IBrainController_1_SpiderBossLocationZone_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x04704558, IBrainControllerExtensions_BuildEntries_12__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_14, (app::IBrainController_1_TimelineBranchingControllerTest_BranchingTestEntries_ * controller))
    IL2CPP_REGISTER_METHODINFO(0x047817D0, IBrainControllerExtensions_BuildEntries_13__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02652700, app::Enum__Array *, BuildEntries_15, (app::IBrainController_1_System_Int32Enum_ * controller))
}
