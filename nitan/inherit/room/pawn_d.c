// /adm/daemons/pawn_d.c
// by Find.

/*
單項記錄格式：
({"find","/obj/book/guwen_book",933947068,"/d/chang/hockshop","這是"})
   ID     pawned ob             到期時間   當鋪物件            stamp long
*/

/* 此功能需要對所有的典當物件進行管理和經常性的檢索操作
 * 對系統資源（CPU & 記憶體）都有很大的消耗，每個玩家所
 * 能典當的物品總數應有限制，還有舉行拍賣大會的時間間隔，
 * 間隔越大負擔越重，目前暫定為每星期3、6晚八點舉行，以
 * 後如必要可改為每星期2、4、6晚舉行。
 * config 裏的 maximum array size 也應足夠大，目前暫設
 * 為 50000。
*/

/* 為統一貨幣單位、直觀利於玩家出價參加競買，所有顯示價
 * 值均轉換成整數銀兩的阿拉伯數字
 */
#define PAWN_STAMP        "/std/room/obj/pawn_stamp"

#include <ansi.h>

inherit F_DBASE;

protected string *all;

protected int max_item_limit = 5;        /* 玩家可典當物品的最大數目 */
protected int be_in_sale_meeting = 0;
protected int min_can_sale_num = 5;        /* 召開拍賣大會所要求的最少的死當物品數量 */

protected void begain_sale_meeting();
protected int find_next_object();
protected void end_sale_meeting();
protected int num_during_meeting = -1;        /* 拍賣大會過程中的物品編號 */
protected object current_object;                /* 正在拍賣的當前物品 */
protected int current_value = 0;                /* 當前價格 */
protected object current_user;                /* 正在出價的玩家 */
protected int min_value_per_chu;                /* 每次加價的最小值 */
protected int unvalid_flag = 0;                /* 當前是否可以出價 */

protected int call_interval = 5;                /* 每次喊價之間的間隔 */
protected int COST = 5;                        /* 拍賣起價折扣 */

void create()
{
        seteuid(getuid());
        set("channel_id", "典當精靈");
}

/* 玩家 login 時由此函數製造當票 */
void restore_players_pawnstamp(object me)
{
        mixed *user_objs;
        object stamp;

        if(!objectp(me) || !userp(me))
                return;

        // 拍賣會期間不處理
        if(be_in_sale_meeting)
                return;

        user_objs = DATABASE_D->query_user_all_pob(geteuid(me));

        if(!user_objs || !sizeof(user_objs))
                return;

        for(int i=0;i<sizeof(user_objs);i++)
        {
                stamp = new(PAWN_STAMP);
                if(!stamp)
                        continue;
                stamp->use_this_stamp(user_objs[i]);
                stamp->move(me);
        }
}

/* 返回一個玩家已典當的所有物品的數量是否已超過最高限 */
int can_pawn_ob(string id)
{
        if(!stringp(id) || id == "")
                return 0;
        else
                return (DATABASE_D->query_count_user_pob(id) < max_item_limit);
}

/* 典當一個物品。
 * return 0        出現錯誤
 * return -1        已達到了玩家可典當物品的最大數目
 * return 1        成功
 */
int pawn_one_object(object stamp)
{
        if(!objectp(stamp) || !stamp->is_pawn_stamp())
                return 0;

        if(!can_pawn_ob( stamp->query_master() ))
                return -1;

        return DATABASE_D->pawn_one_object( stamp->query_all_msg() );
}

/* 贖回一個物品。
 * return 0        出現錯誤
 * return -1        沒有典當過這個物品
 * return 1        成功
 *
 * 此函數沒有進行是否已過期檢查。
 * 主要留待於另一個想法：
 * 目前物品過期就不能再贖回了，只能拍賣大會上見，
 * 過期檢查在 HOCKSHOP 物件裏。
 * 是否可以物品在過期後與上拍賣大會前的一段時間裏
 * 還可贖回，不過要用兩倍的價格買回作為懲罰？
 * 如這樣 HOCKSHOP 裏要作相應的修改，return -1
 * 也具有了不同的意義---即：已賣出。
 * restore_players_pawnstamp 函數裏對過期的當票也
 * 應交付玩家，可以把當票名稱改成“過期的當票”。
 * 是否如此有待於討論。
 */
int redeem_one_object(object stamp)
{
        if(!objectp(stamp) || !stamp->is_pawn_stamp())
                return 0;

        return DATABASE_D->retrieve_one_object(stamp->query_master(),stamp->query_rtime());
}

// 以下為拍賣大會部分：
void touch_meeting()
{
        object selling_room;

        if(!previous_object() || (geteuid(previous_object()) != ROOT_UID))
                return;

        if(be_in_sale_meeting)
                return;
        else
        {
                if(selling_room = find_object("/d/changan/selling_room"))
                        selling_room->begin_paimai_meeting();
                be_in_sale_meeting = 1;
                begain_sale_meeting();
                return;
        }
}

protected int can_begain_meeting()
{
        all = DATABASE_D->query_all_exceed_pob();
        return sizeof(all) >= min_can_sale_num;
}

protected void begain_sale_meeting()
{
        int year = NATURE_D->query_year();

        if(!can_begain_meeting())
        {
                CHANNEL_D->do_channel( this_object(), "paimai",sprintf("◆%s創世%s年度全國拍賣大會通告◆："+
                "本屆拍賣大會由於死當物品過少，決定取消！！",MUD_NAME,(!year)?"元":chinese_number(year)));
                be_in_sale_meeting = 0;
                return;
        }

        CHANNEL_D->do_channel( this_object(), "paimai",sprintf("%s創世%s年度全國拍賣大會現在開幕！"+
                "歡迎各界人士參加競買！！",MUD_NAME,(!year)?"元":chinese_number(year)));
        call_out("teach_rules",2);
        return;
}

protected void teach_rules()
{
        CHANNEL_D->do_channel( this_object(), "paimai",
                      "參加競買人士可以使用 chu <銀兩數> 命令對當前拍賣物品出價，\n"+
        "              表示你願意出多少兩銀子購買當前拍賣物品。\n");
        call_out("lasting_sale_objs",5,0);
}

protected void reset_variable()
{
        current_object = 0;                /* 正在拍賣的當前物品 */
        current_value = 0;                /* 當前價格 */
        current_user = 0;                /* 正在出價的玩家 */
        min_value_per_chu = 0;                /* 每次加價的最小值 */
}

protected void give_obj_to_user()
{
        int cant_hold_flag;

        CHANNEL_D->do_channel( this_object(), "paimai",sprintf("恭喜%s(%s)以 %d 兩銀子購得 %s"+HIY+"。\n",
                query("name", current_user),geteuid(current_user),
                (current_value/100),current_object->name()));

        if(pay_from_bank(current_user,current_value))
        {
                if(!current_object->move(current_user))
                {
                        cant_hold_flag = 1;
                        current_object->move(environment(current_user));
                }

                tell_object(current_user,sprintf("一個小夥計滿頭大汗地跑到你跟前説道：“這是您買的東西%s。”\n",
                        (cant_hold_flag)?"給您放地上了":"您收好" ));
        }
        else
                tell_object(current_user,"你的銀行存款不夠！\n");

        delete_temp("be_in_sale_meeting_chu", current_user);

        reset_variable();
}

protected void lasting_sale_objs(int when)
{
        int value;

        remove_call_out("lasting_sale_objs");

        if(num_during_meeting == -1) // 還未開始拍賣
        {
                num_during_meeting = 0;
                find_next_object();
                if( !value=query("value", current_object) )
                        value = current_object->value();
                current_value = to_int(ceil(value/10*COST/100))*100;
                min_value_per_chu = to_int(ceil(value/1000))*100;
                CHANNEL_D->do_channel( this_object(), "paimai","大會正式開始，第一件物品：\n"+
                        sprintf("             %s"+HIY+"一%s，原價 %d 兩白銀：，起價：%d 兩白銀\n"+
                                "             每次出價至少要高於當前價格 %d 兩白銀，請有意者出價。\n",
                                current_object->name(),(query("unit", current_object))?
                                query("unit", current_object):"件",to_int(ceil(value/100)),
                                (current_value/100),(min_value_per_chu/100)));
                unvalid_flag = 0;
                call_out("lasting_sale_objs",call_interval+2,0);
                return;
        }

        if(!when)        // 新價格或者新物品出來後進行一次詢問
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("%s"+HIY+"當前價格：%d 兩白銀，%s？\n",current_object->name(),
                        (current_value/100),
                        (current_user)?"還有人出更高的價格嗎":"有人對這個價格感興趣嗎"));
                call_out("lasting_sale_objs",call_interval,1);
                return;
        }

        if(when == 1)        // 第一次計數
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("當前物品：%s"+HIY+"，%d 兩白銀 第一次！有興趣的快出價啦！\n",current_object->name(),
                        (current_value/100)));
                call_out("lasting_sale_objs",call_interval,2);
                return;
        }

        if(when == 2)        // 第二次計數
        {
                CHANNEL_D->do_channel( this_object(), "paimai",
                        sprintf("當前物品：%s"+HIY+"，%d 兩白銀 第二次！機會難得呀！\n",current_object->name(),
                        (current_value/100)));
                call_out("lasting_sale_objs",call_interval,3);
                return;
        }

        if(when == 3)
        {
                unvalid_flag = 1;
                if(current_user)
                        give_obj_to_user();
                else
                        reset_variable();
                if(!find_next_object())
                {
                        end_sale_meeting();
                        return;
                }
                else
                {
                        if( !value=query("value", current_object) )
                                value = current_object->value();
                        current_value = to_int(ceil(value/10*COST/100))*100;
                        min_value_per_chu = to_int(ceil(value/1000))*100;
                        CHANNEL_D->do_channel( this_object(), "paimai","繼續進行下一件物品：\n"+
                                sprintf("             %s"+HIY+"一%s，原價 %d 兩白銀：，起價：%d 兩白銀\n"+
                                "             每次出價至少要高於當前價格 %d 兩白銀，請有意者出價。\n",
                                current_object->name(),(query("unit", current_object))?
                                query("unit", current_object):"件",(value/100),
                                (current_value/100),(min_value_per_chu/100)));
                        unvalid_flag = 0;
                        call_out("lasting_sale_objs",call_interval+2,0);
                        return;
                }
        }
}

/*
 * return 0 已沒有可拍賣的物品了
 * return 1 找到下一個可拍賣的物品
 */
protected int find_next_object()
{
        while(1)
        {
                if(num_during_meeting >= sizeof(all))
                        return 0;

                current_object = new(all[num_during_meeting]);
                if(!objectp(current_object))
                        all -= ({ all[num_during_meeting] });
                else
                {
                        num_during_meeting++;
                        return 1;
                }
        }
}

protected void end_sale_meeting()
{

        CHANNEL_D->do_channel( this_object(), "paimai","本屆拍賣大會圓滿結束。");

        all = 0;
        num_during_meeting = -1;
        be_in_sale_meeting = 0;
}

int query_being_meeting()
{
        return be_in_sale_meeting;
}

int query_num_during_meeting()
{
        return num_during_meeting;
}

int query_unvalid_flag()
{
        return unvalid_flag;
}

object query_current_user()
{
        return current_user;
}

int query_current_value()
{
        return current_value;
}

int query_min_value_per_chu()
{
        return min_value_per_chu;
}

/* 接受玩家的出價 */
void accept_chujia(object usr,int value)
{
        if(!usr || (current_user == usr))
                return;

        if(find_call_out("lasting_sale_objs"))
                remove_call_out("lasting_sale_objs");

        if(objectp(current_user))
                delete_temp("be_in_sale_meeting_chu",1, current_user);

        current_user = usr;
        current_value = value;

        CHANNEL_D->do_channel( this_object(), "paimai",
                sprintf("%s(%s)出價 %d 兩白銀競買 %s"+HIY+"。\n",
                query("name", current_user),geteuid(current_user),
                current_value/100,current_object->name()));

        call_out("lasting_sale_objs",call_interval,0);
        return;
}