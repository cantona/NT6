#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "【天外桃源】" NOR);
        set("long", HIM @LONG

                天     外     桃      源
    天空的盡頭是一處桃源勝地，宇宙似乎沒有終點，你始終能發現
不一樣的天地，四周紫氣氤氳，白雲繚繞，難道是傳說中的仙境？琴
音又再響起，但似乎聽得更加清晰了，隱約間，你面前出現了一位熟
悉的青年，他隨意撥弄著古琴，陣陣天籟之音令你心曠神怡。你只想
永遠留在此處，不再理會人間的紛爭與情仇。
LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tianshen2": 1,
        ]));
        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // 不能騎馬或MISS到這裡，已經在horse.c做限制
        set("no_rideto", 1);   // 不能騎馬或MISS到這裡，已經在horse.c做限制
        set("no_obsend", 1);
        set("no_paimai", 1);
        set("sky", 1);
        
        setup();
}

void init()
{
        object me = this_player();
        
        tell_object(me, HIG "\n恭喜你，已經完成所有二轉任務，與天神對話即可完成二轉！\n" NOR);
}
