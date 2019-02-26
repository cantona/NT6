#include <ansi.h>
inherit ROOM;

#define MEMBER_D          "/adm/daemons/memberd"

void create()
{
        set("short", "海灘");
        set("long", @LONG
這裏就是蓬萊仙島了。北邊是一望無際的大海，放眼望去，整
個島被仙氣籠罩，前方不遠處是一片竹林，陣陣梵音傳出，令人心
曠神怡。
LONG);

        set("exits",([
                "south" :__DIR__"zhulin1",
        ]));
        set("outdoors", "penglai");
        set("valid_startroom", 1);
        set("no_clean_up", 1);
        set("no_rideto", 1);         // 設置不能騎馬到其他地方
        set("no_flyto", 1);          // 設置不能從起來地方騎馬來這裏
        set("no_die", 1);            // 死亡後移動到扁鵲居
        set("penglai", 1);           // 表示在蓬萊島 
        set("no_fight", 1);       

        set("objects", ([
               // __DIR__"npc/milu-shangren" : 1,
        ]));
       
        setup();
        "/clone/board/penglai_shibi"->foo(); 
}

void init()
{
        if (base_name(this_player()) == "/d/penglai/npc/qingmianshou")
        {
                destruct(this_player());
                return;
        }
                
        if (! GIFT_D->is_open_pld())
        {
                   // 活動結束了，移動回客店
                   if (random(2))
                   {
                           this_player()->move("/d/city/wumiao");
                           this_player()->set("startroom", "/d/city/wumiao");
                   }
                   else
                   {
                           this_player()->move("/d/city/kedian");
                           this_player()->set("startroom", "/d/city/kedian");
                   }


        }
        this_player()->set("startroom", base_name(this_object()));
        this_player()->save();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir == "south")
        {
                if (! MEMBER_D->is_valib_member(me->query("id")))
                        return notify_fail("只允許有效會員進入蓬萊島！\n");
        }

        return 1;
}
