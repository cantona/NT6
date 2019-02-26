// Room: /d/yanping/yanxianshan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "衍仙山");
        set("long", @LONG
傳説晉代延平人衍客結廬於此煉丹成佛。此處峯巒危巖嶙峋，草木
薈蔚，山花爛熳，澗泉爽人，景色奇麗，文人美稱其為“衍麓晴霞”，
列為延平八景之一。詩人頌之曰：“仙人何去住，丹炷演山前。天開雲
錦爛，疑是紫爐煙。”
　　巖壁上巍然屹立着一尊巧奪天工的天然石佛，高約五丈，頭稍俯視。
在其背後的山麓上，還有酷似坐式石佛的塊巖。
LONG );
        set("exits", ([
                "northeast" : __DIR__"gubao",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1480);
        set("coor/y", -6120);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}