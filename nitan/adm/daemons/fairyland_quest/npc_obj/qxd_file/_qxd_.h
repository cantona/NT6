// qxd 主文件，由上級目錄  _qxd_.c 以 #include 調用。
// naihe 3:15 03-10-19
// 各項順序不得調亂，各項不得缺少。


#define    HJ_OUT_ROOM    HJ_DIR + "room_gameover_hj"

#include "1_vars_qxd.h"         // 文件頭的變量設定

#include "2_preload_qxd.h"      // 預裝函數，全局各處要用

#include "3_file_qxd.h"         // create() 及其他主要功能

#include "4_cmds_qxd.h"         // 支持玩家基本指令

#include "4-1_cmds_qxd.h"       // 越寫越多，寫不下了，放到這裡

//#include "5_help_qxd.h"         // help 函數   help 函數取消了。

#include "6_combat_qxd.h"       // 戰鬥相關指令

#include "7_pfm_qxd.h"          // 絕招支持

