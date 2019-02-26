// Room: /d/yueyang/qiuyueting.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "秋月亭");
        set("long", @LONG
秋月亭、秋月橋、秋月井皆出自於宋朝畫家米芾名畫《瀟湘八景》
之《洞庭秋月》這個掌故。秋月亭建於君山東側小山秋月嶺上，始建於
宋末，為單層檐六個方亭，亭中有兩人觀月台。站在亭上可以飽覽洞庭
湖月色(moon)。傳説米芾就是在這裏完成了他的名畫《洞庭秋月》。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("item_desc", ([
                "moon" : "
    月下的洞庭，安然恬靜如閨閣閒情裏的典雅淑女，絕無喧譁，絕無
牽絆，絕無爭執，絕無傷害。這是一種奇妙的造化，是洞庭湖在月夜裏
展示出來的屬於它另一面的陰柔之美，它的美無所不在。\n"
        ]));
        set("exits", ([
                "southdown" : __DIR__"qiuyueqiao",
                "northeast" : __DIR__"xiaolu8",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2340);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}