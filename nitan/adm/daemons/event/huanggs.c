// puliu.c 事件：黃果樹瀑布

#include <ansi.h>

void create() { seteuid(getuid()); }

// 開始創建事件
void create_event()
{
        // 明天5點鐘瀑流最急
        EVENT_D->at_after(0, 0, 1, -5);
}

// 獎勵
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl;
        int r;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        { 
                msg = HIR "只聽轟隆隆聲音大做，發耳欲聵，令人心神俱搖！你抬頭看去，只見\n"
                          "晨曦中黃果樹瀑布籠罩着層層霧氣，分外要人。水流飛瀉，氣勢驚人！\n" NOR;
                msg += HIG "你望着湍急的瀑布飛練，為這世間美景驚歎不已，從"
                           "中不禁領悟到了武學的道理。\n" NOR; 

                for( int i=0; i<sizeof(obs); i++ )
                {
                        addn("combat_exp", 1000, obs[i]);
                        addn("potential", 500, obs[i]);
                }

                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "黃果樹激流", this_object());

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽説黃果樹激流澎湃，奇景非凡，無數遊人歎羨不已。");
        } else 
        if (r < 250) 
        {
                msg = HIY "一陣轟隆轟隆的聲音傳來，你抬頭一看，只見晨曦中瀑布騰起層層霧氣。\n" NOR;
                switch (random(3)) 
                { 
                case 0: 
                        msg += HIY "看着這壯麗的瀑流，你不禁感歎，正所謂「飛流直"
                                    "下三千尺，疑是銀河落九天」啊。\n" NOR; 
                        break; 
                case 1: 
                        msg += HIY "瀑流就像一席倒掛的白簾，氣勢如虹，天地都不禁為之失色。\n" NOR; 
                        break; 
                default: 

                        msg += HIY "瀑流直如水銀泄地一般，水花四濺。\n" NOR; 
                        break; 
                } 
                msg += HIG "觀賞着飛流直下的水瀑，你不由得感歎自然造化的奇妙，隱"
                           "隱然對武學也有了一點領會。\n" NOR; 

                for( int i=0; i<sizeof(obs); i++ )
                {
                        obs[i]->improve_potential(5 + random(7));
                        addn("combat_exp", 20+random(10), obs[i]);
                }
 
                message("vision", msg, obs);

                // 記錄事件
                MAP_D->record_rumor(obs, "黃果樹瀑布", this_object());
        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "瀑流漸漸緩了下來。\n" NOR;
                        break;
                case 1:
                        msg = WHT "瀑流總是不見有增強的趨勢。\n" NOR;
                        break;
                default:
                        msg = WHT "瀑流有如小橋流水，叮叮咚咚，離你所期望的相差甚遠。\n" NOR;
                        break;
                }
                msg += HIG "你心中大感失望。\n" NOR;

                message("vision", msg, obs);
        }
} 
 
// 事件觸發 
void trigger_event() 
{ 
        object room; 
        // 黃果樹瀑流 
        if (objectp(room = find_object("/d/dali/huanggs"))) 
                do_bonus(room); 
 
        create_event(); 
} 

// 描述 
string query_detail(string topic) 
{ 
        switch (topic) 
        { 
        case "黃果樹激流": 
                return "黃果樹瀑布水流湍急，時有激流澎湃，乃是罕見的景觀。\n"; 
 
        case "黃果樹瀑布": 
                return "大理的黃果樹瀑布自然風光迷人，瀑流美麗壯觀。\n"; 
        }
} 
