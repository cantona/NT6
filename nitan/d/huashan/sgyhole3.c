// Room: /d/huashan/sgyhole.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "山洞");
        set("long", @LONG
這是一個毫不起眼的山洞，但是裡面的石壁上卻畫滿了五岳劍派
所有已經失傳的精妙絕招。花崗巖石壁(wall)上很多小人，全是用利
器刻制，想見當初運力之人內力十分深厚。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "southup"   : __DIR__"sgyhole2",
            "north"     : __DIR__"sgyhole4",
        ]));
        set("item_desc", ([ 
            "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L

TEXT
        ]));

        setup();
}
void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("poyang-jian", 1);


        if( !query("can_perform/poyang-jian/long", ob) )
        {
                write("你覺得石壁上的內容對你而言過于深奧，一時難以體會。\n");
                return 1;
        }

        if( query("real_perform/poyang-jian/long", ob) )
        {
                write("你覺得石壁上的內容對你而言過于膚淺。\n");
                return 1;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                write("你的實戰經驗不足，無法領悟石壁內容。\n");
                return 1; 
        }

        if (c_skill < 160)
        {
                write("你研究了半天，始終無法參悟透石壁上的內容。\n");
                return 1; 
        }

        if( query("jing", ob)<80 )
        {
                write("你精力不能集中，現在無法領悟石壁內容。\n",ob);
                return 1; 
        }
      
        if (random(15) != 1)
        {
        
                write("你面對著石壁趺坐靜思，良久，對「天外玉龍」"
                               "這招似有所悟，但仍有許多不解之處。\n", ob);
                ob->start_bisy(2);
                return 1;
        }

        message_sort(HIW"\n$N" HIW"面對著石壁趺坐靜思，猛然間一聲長嘆，諸"
                     "多凡塵舊事已湧上心頭，$N" HIW "終于將「天外玉龍」"
                     "參悟出來，從此再無疑慮。\n", ob);

        if (ob->can_improve_skill("sword"))
                 ob->improve_skill("sword", 1500000);   
        if (ob->can_improve_skill("poyang-jian"))
                 ob->improve_skill("poyang-jian", 1500000);     
        if (ob->can_improve_skill("martial-cognize"))
                 ob->improve_skill("martial-cognize", 1500000);
    
        write(HIC "你學會了「天外玉龍」。\n" NOR);
        set("real_perform/poyang-jian/long", 1, ob);
        ob->receive_damage("jing", 75);
        ob->start_busy(2);
        return 1;
}