// quest.h

// QUEST基礎對象
#define QUEST_OB                "/inherit/misc/quest"

// 任務對象的函數
varargs string name();
varargs string query_introduce(object knower, object who);
varargs int    can_know_by(object knower);
varargs int    can_rumor_by(object knower);

// 功能函數
varargs void   set_information(string key, string info);
varargs void   set_name(string name);

// 狀態機函數
string  query_status();
void    change_status(string new_state);

// 任務對象的系統狀態
#define QUEST_CREATE            "created" /* 任務創建     */
#define QUEST_READY             "ready"   /* 任務就緒     */
#define QUEST_FINISH            "finish"  /* 任務完成     */
#define QUEST_ERROR             "error"   /* 任務錯誤狀態 */

// 任務對象的系統事件
#define QUEST_TIMEOUT           "timeout" /* 任務超時     */

// 在創建狀態最長的停留時間
#define QUEST_CREATE_PERIOD     30

// 在結束狀態最長的停留時間
#define QUEST_FINISH_PERIOD     30

void    register_information();
