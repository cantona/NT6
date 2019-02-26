inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山行崎嶇，這裏已是雪山之上，朔風飛揚，黃雲蓋天。愈上
愈高，山勢也愈來愈險，俯覽羣山，片片浮白，在雲氣瀰漫之下，
恍如雲海中星羅棋佈的島嶼。這時已是正午時分，但寒氣卻愈來
愈濃。四周白茫茫的一片，惟有無邊飛雪，紛紛揚揚從空中撒將
下來。
LONG);
        set("outdoors", "lingxiao");
        set("exits",([
                    "southdown"  : __DIR__"sroad2",
                    "eastup"  : __DIR__"shiya",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/huyanwanshan" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
