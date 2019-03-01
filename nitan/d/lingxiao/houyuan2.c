inherit ROOM;

void create()
{
        set("short","後園");
        set("long",@LONG 
這裡重門疊戶，是凌霄城上層人物的居所了。一般弟子要是
沒什麼事，是不能隨便進來的。旁邊幾叢綠竹，鬱鬱蔥蔥。屋柱
上盡皆雕鏤著雪花六出之形，一盆盆梅花栽種在屋廊之中。比起
外面合圍粗的各色梅樹，又是別有風情，左邊是白萬劍的家，右
邊是封萬裡的住所。
LONG);
        set("outdoors", "lingxiao");
        set("exits",([
                    "south"  : __DIR__"houyuan1",  
                    "north"  : __DIR__"bridge", 
                    "west"  : __DIR__"qihan", 
                    "northwest"  : __DIR__"zoulang3", 
                    "northeast"  : __DIR__"zoulang4", 
                    "east"  : __DIR__"fenghuo", 
        ]));
        set("objects", ([ 
                   __DIR__"obj/mei" : 2, 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
