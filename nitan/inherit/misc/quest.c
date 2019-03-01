// inherit object: quest.c
// 所有玩家任務繼承此對象

#include <quest.h>

inherit F_DBASE;

mixed quest_name;

nosave int destructing;         // 析構對象時候的標志
nosave string status;           // 任務對象的狀態

int is_quest() { return clonep(this_object()); }

// 任務的名字
varargs string name()
{
        if( stringp(quest_name) )
                return quest_name;

        if( functionp(quest_name) )
                return evaluate(quest_name);

        return "未名任務";
}

// 設置名字
void set_name(string name)
{
        quest_name = name;
}

// 該任務消息靈通人士(knower)對某人(who)而言的介紹
varargs string query_introduce(object knower, object who)
{
        // 缺省是沒有介紹的 - 能夠被散布的應該必須有介紹。
        return 0;
}

// 該任務是否能被消息靈通人士(knower)所知曉
varargs int can_know_by(object knower)
{
        // 缺省是可以知曉的
        return 1;
}

// 該任務是否能被消息靈通人士(knower)廣為散布
varargs int can_rumor_by(object knower)
{
        // 缺省只要該人知道就可以散布
        // 必須引用this_object()，因為can_know_by() 一般會被
        // 具體的任務對象重載，如果不引用this_object()就調用
        // 不了重載的函數。
        return this_object()->can_know_by(knower);
}

// 任務的初始化
void setup()
{
        if( !this_object()->is_quest() )
                return;

        // 這是一個任務
        status = QUEST_CREATE;
        set("start_time", time());
        QUEST_D->add_quest(this_object());
}

// 任務的析構函數。
// 如果是首先析構這個任務對象，則destructing這個標識必然為零，
// 那麼我就設置標識，然後嘗試調用取消任務的重載函數。 這樣在
// 取消任務的函數中調用析構函數就不會再次執行。
void remove()
{
        if( !destructing && this_object()->is_quest() ) {
                destructing = 1;

                // 在析構前取消任務
                this_object()->cancel_quest();
        }
}

// 結束任務的函數
// 直接調用析構函數
void cancel_quest()
{
        // 設置結束時間
        set("finish_time", time());

        // 從QUEST_D中去掉有關這個對象的信息
        QUEST_D->remove_all_information(this_object());

        // 如果沒有析構這個任務，則設置標識，然後析構這個任務
        if( !destructing ) {
                destructing = 1;
                destruct(this_object());
        }
}

// 查詢任務狀態
string query_status()
{
        return status;
}

// 任務改變狀態
void change_status(string new_state)
{
        if( status == new_state )
                // 狀態沒有變化
                return;

        status = new_state;
        if( status == QUEST_FINISH ) {
                // 遷移到結束狀態？析構對象。
                destruct(this_object());
        }
}

// 在QUEST_D那裡登記一條消息
void set_information(string key, string info)
{
        QUEST_D->set_information(this_object(), key, info);
}

// 在QUEST_D那裡登記自己的消息
void register_information()
{
        // 必須登記一定的信息才可以
}