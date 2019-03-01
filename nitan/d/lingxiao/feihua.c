inherit ROOM;

void create()
{
        set("short","飛花閣");
        set("long",@LONG 
這是凌霄城第六代弟子，「寒梅女俠」花萬紫的居所，樓名
飛花閣。花萬紫是凌霄城六代弟子中唯一的女性，一來因為避嫌，
二來花萬紫本就性喜清凈，故一人獨居于此。此處是花園小樓之
上，憑窗而望，千萬朵梅花迎雪飛舞，萬梅飄零，紛紛而下。桌
上放著一束五顏六色的梅花。
LONG);
        set("outdoors", "lingxiao");
        set("exits",([
            "down"  : __DIR__"huajing",  
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/huawanzi" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
