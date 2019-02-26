// /d/gaoli/yingbinguan.c
// Room in 高麗
inherit ROOM;

string look_sign(object me);

void create()        
{
        set("short", "迎賓館");
        set("long", @LONG
你現在正站在高麗的迎賓館裏，迎賓館不僅招待使節，還招待各路
客商，來自中原的旅人都喜歡聚集在這裏交換旅途上的見聞，你也可以
在這裏打聽到許多有趣的消息。靠近門口的地方有一塊烏木雕成的招牌
(sign)。
LONG
        );
set("valid_startroom", 1);
set("item_desc", ([
                "sign": (: look_sign :),
                ]));
set("exits", ([
                "north":__DIR__"yudao8",
                "up":__DIR__"kefang",
        ]));
       setup();
        
        
set("objects", ([
        __DIR__"npc/xiaoer" : 1, 
]));

        setup();
        }


string look_sign(object me)
{
        if( wizardp(me) )
    return "招牌寫著：猛鬼客棧。\n";
        else
        return "招牌寫著：內設雅房，每夜五兩白銀。\n";
}
int valid_leave(object me, string dir)
{

        if ( !me->query_temp("rent_paid") && dir == "up"&&me->query("family/family_name")!="弈劍派" )
                return notify_fail("怎麼着，想白住啊！\n");

        if ( me->query_temp("rent_paid") && dir == "north" )
                return notify_fail("客官已經付了銀子，怎麼不住店就走了呢！旁人還以為小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}
