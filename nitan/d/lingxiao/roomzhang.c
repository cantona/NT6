inherit ROOM;
void create()
{
        set("short", "居室");
        set("long", @LONG 
走進這裏，出現在你眼前的是大大小小的藥罐。在這裏住的
是凌霄城的六代弟子張萬風，他為人厚道，所以白自在放心地把
管理凌霄城一些稀世藥物的任務交給了他。不過據説他跟王萬仞
向來交好，經常把一些珍貴的藥酒給那傢伙喝。
LONG);
        set("exits",([
                    "north"  : __DIR__"zoulang2", 
        ]));
        set("objects", ([  
                CLASS_D("lingxiao") + "/zhangwanfeng" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
