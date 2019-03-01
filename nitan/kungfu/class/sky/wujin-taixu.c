
#include <ansi.h>

inherit ITEM;

void setup()
{

        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // 不能騎馬或MISS到這裡，已經在horse.c做限制
        set("no_rideto", 1);   // 不能騎馬或MISS到這裡，已經在horse.c做限制
        set("no_obsend", 1);
        set("no_paimai", 1);

        ::setup();

}

void create()
{
        set_name(HIW "無盡太虛" NOR, ({ "wujin taixu" }));
        set_weight(200000);
        set_max_encumbrance(2000000000);

        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                set("long",
                HIY "這裡是宇宙之深淵，無盡的太虛，四周白茫茫一片，似乎沒有前進之路，\n"
                    "也沒有邊際。不時有陣陣琴音傳出，幽雅而又意味深長，令你不禁回想起這\n"
                    "一生，經過了多少恩怨情仇，經過了多少血腥與殺戮，在這浩瀚無邊際的宇\n"
                    "宙之中，你只不過是一粒細小的塵埃，亦或在上天眾神眼中你只不過是一只\n"
                    "微不足道的螻蟻 …… 琴音時而委婉，時而高亢，隨著琴音起伏，你心中思\n"
                    "緒萬千 ……\n"NOR);
                set("unit", "處");
                set("material", "air");
                set("no_rideto", 1);
                set("no_flyto", 1); 
                set("exits", ([ "out" : "/kungfu/class/sky/sky13" ]));
             
                set("no_get", "!@#$!@#%%^@!^\n");
        }
        setup();
}
/*
void init()
{
        object me = this_player();
        
        add_action("do_start", "start");
        
        CHANNEL_D->do_channel("rumor", this_object(), HIY + me->name() + "(" + me->query("id") + ")" HIM "被炎黃天神送入無盡太虛，挑戰二轉守護神！\n" NOR);                
}
*/


int valid_leave(object me, string arg)
{
        return 1;
}
