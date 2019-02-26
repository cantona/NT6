// npc: /d/city/npc/jiangqianli.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>

inherit NPC;

void create()
{   
        set_name(YEL "江千里" NOR, ({ "jiang qianli","jiang" }) );
        set("gender", "男性");
        set("title", "江氏漆器作坊主");
        set("age", 38);
        set("long", @LONG
他是揚州城裏最好的漆器手工藝人，中等身材，四方臉，看上去一團和氣。
只有兩手的手指纖細修長顯出他是個手工藝人。
LONG
        );
        set("attitude", "peaceful");

        set("str", 17);
        set("int", 30);
        set("dex", 30);
        set("con", 30);
        set("per", 20);

        set("combat_exp", 100000);
        set("score", 9000);

        set("inquiry", ([
                "江千里" : "江千里就是我。本人姓江名千里，表字秋水。\n",
                "漆沙硯" : "此硯乃是先祖竭盡心思所創，歷經十年才盡善盡美。",
                "螺鈿杯" : "承蒙朋友捧場，送了一首詩：\n"+
                        "                        螺鈿粧成翡翠光，紫霞秋澈婺州香\n"+
                        "                        形神俱美真通太，假寐仍期到夢鄉\n",
        ]) );


        setup();

}
