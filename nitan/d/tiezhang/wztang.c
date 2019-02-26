#include <ansi.h>

inherit ROOM;
string look_bian();

void create()
{
        set("short", HIY "五指堂" NOR);
        set("long", @LONG
這是一間完全用花崗巖砌成的大廳，透出陣陣逼人的寒氣。整座房內沒
有窗户，顯得陰森黑暗。兩旁的牆壁上插着松油制的火把，散發出昏黃色的
光亮，寂靜的大廳中不時響起火把噼啪的燃燒聲。大廳的正中擺放着幫主的
寶座，兩旁分列着十幾把椅子，只有遇到幫中大事時，幫主才會在這裏與部
下商議。在正面的牆上掛着一面縷金的橫匾(bian)。北面有一扇小門通向後
面。
LONG );

        set("item_desc", ([ 
                "bian"       :       (: look_bian :),
        ]));

        set("exits", ([ 
                "east" : __DIR__"zoulang-1",
                "southdown" : __DIR__"guangchang",
                "west" : __DIR__"zoulang-2",
                "north" : __DIR__"hxfang",
        ]));
        set("objects", ([ 
                CLASS_D("tiezhang") + "/qiuqianren" : 1,
                __DIR__"npc/xiaotong" : 2,
        ]));

        set("no_clean_up", 0);
        set("valid_startroom", 1);
        setup();
}

string look_bian()
{
    return
    "\n"
              HIY "          ####################################\n"
                  "          ####                            ####\n"
                  "          ####    五    指    擎    天    ####\n"  
                  "          ####                            ####\n"
                  "          ####################################\n\n\n\n\n\n\n" NOR;
    "\n";
}