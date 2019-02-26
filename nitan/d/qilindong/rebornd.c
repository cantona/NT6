
//轉世任務主控文件
#include <ansi.h>

inherit F_DBASE;

#define JINGYAN  "/d/jingyan/migong1"
#define QILIN  "/d/zhuanshi/qilindong/dongkou"
#define WUDIE  "/d/wudie/shanlu1"

void jingyan_close(object n_place);
void wudie_close(object n_place);
void qilin_close(object place);

mapping dir_list = ([
"北京" : "/d/beijing/",
"長安" : "/d/changan/",
"揚州" : "/d/city/",
"成都" : "/d/city3/",
"大理" : "/d/dali/",
"佛山" : "/d/foshan/",
"福州" : "/d/fuzhou/",
"關外" : "/d/guanwai/",
"杭州" : "/d/hangzhou/",
"恆山" : "/d/hengshan/",
"荊州" : "/d/jingzhou/",
"開封" : "/d/kaifeng/",
"華山" : "/d/huashan/",
"昆明" : "/d/kunming/",
"蘭州" : "/d/lanzhou/",
"靈州" : "/d/lingzhou/",
"洛陽" : "/d/luoyang/",
"嵩山" : "/d/songshan/",
"蘇州" : "/d/suzhou/",
"泰山" : "/d/taishan/",
"武當山" : "/d/wudang/",
"襄陽" : "/d/xiangyang/",
"中州" : "/d/zhongzhou/",
]);

array place = values(dir_list);
array c_place = keys(dir_list);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "轉世精靈");
        CHANNEL_D->do_channel( this_object(), "wiz", "轉世精靈啟動。"); 
        //驚雁宮入口
        remove_call_out("jingyan_open");
        call_out("jingyan_open", 350);
                //舞蝶入口
        remove_call_out("wudie_open");
        call_out("wudie_open", 350);
       //麒麟窟入口
        remove_call_out("qilin_open");
        call_out("qilin_open", 550);
}

void jingyan_open()
{       
        object n_place;
        string s_place, dir;
        int i;
        int num = random(sizeof(place));
        string city = place[num];

        array plist = get_dir(city);

        do {       
                s_place = plist[random(sizeof(plist))];     
                //文件名中含有bak的文件不要，繼續找下一個
                if ( strsrch(s_place,"bak") > -1 ) continue; 
                //不是c文件的也濾過
                i = sizeof(s_place);
                if ( s_place[(i-2)..i] != ".c" ) continue;
                //如果該房間已經調出在內存裏的直接find
                //find不到説明沒調出在內存裏，那就load出來 
                //load也load不出來大概就有問題了，那就找下一個了   
                if ( ! objectp(n_place = find_object(city + s_place)))
               
                if ( ! objectp(n_place = load_object(city + s_place)))
                   continue; 
           }       
        while(!n_place || !n_place->query("outdoors"));
                
        n_place->set("exits/jingyangong", JINGYAN);

               
       CHANNEL_D->do_channel(this_object(), 
         "wiz", "驚雁宮入口連接到了" + c_place[num] + city + s_place + "請注意。");
                
       set("jingyan/out", city + s_place); //主文件裏記錄下迷宮的連接處
                                          
       message("vision", HIG"【" HIR "江湖傳言" HIG"】" HIW 
               "：神祕的驚雁宮重現江湖了，似乎在"
               + c_place[num] + "方向。\n" + NOR,users());
       //10分鐘後關閉，時間可以設置

       remove_call_out("jingyan_close");
       call_out("jingyan_close", 600, n_place);      
}

void jingyan_close(object n_place)
{       
     if (n_place && n_place->query("exits/jingyangong"))
     {       
       n_place->delete("exits/jingyangong");       
       message("vision", HIG"【" HIR"江湖傳言" HIG"】" HIW"：神祕的驚雁宮又消失了。\n" 
                      NOR,users());
     }
     remove_call_out("jingyan_open");
   //  call_out("jingyan_open", 3600 * 3); //定三小時開一次口
     call_out("jingyan_open", 1800); //測試時定半小時開一次口

}
void wudie_open()
{       
        object n_place;
        string s_place, dir;
        int i;
        int num = random(sizeof(place));
        string city = place[num];

        array plist = get_dir(city);

        do {       
                s_place = plist[random(sizeof(plist))];     
                //文件名中含有bak的文件不要，繼續找下一個
                if ( strsrch(s_place,"bak") > -1 ) continue; 
                //不是c文件的也濾過
                i = sizeof(s_place);
                if ( s_place[(i-2)..i] != ".c" ) continue;
                //如果該房間已經調出在內存裏的直接find
                //find不到説明沒調出在內存裏，那就load出來 
                //load也load不出來大概就有問題了，那就找下一個了   
                if ( ! objectp(n_place = find_object(city + s_place)))
               
                if ( ! objectp(n_place = load_object(city + s_place)))
                   continue; 
           }       
        while(!n_place || !n_place->query("outdoors"));
                
        n_place->set("exits/wudie", WUDIE);

               
       CHANNEL_D->do_channel(this_object(), 
         "wiz", "舞蝶山莊連接到了" + c_place[num] + city + s_place + "請注意。");
                
       set("wudie/out", city + s_place); //主文件裏記錄下迷宮的連接處
                                          
       message("vision", HIG"【" HIR "神祕門派" HIG"】" HIW 
               "：傳説中的舞蝶山莊重現江湖了，似乎在"
               + c_place[num] + "方向。\n" + NOR,users());
       //10分鐘後關閉，時間可以設置

       remove_call_out("wudie_close");
       call_out("wudie_close", 600, n_place);      
}

void wudie_close(object n_place)
{       
     if (n_place && n_place->query("exits/wudie"))
     {       
       n_place->delete("exits/wudie");       
       message("vision", HIG"【" HIR"神祕門派" HIG"】" HIW"：傳説中的舞蝶山莊又消失了。\n" 
                      NOR,users());
     }
     remove_call_out("wudie_open");
   //  call_out("jingyan_open", 3600 * 3); //定三小時開一次口
     call_out("wudie_open", 1800); //測試時定半小時開一次口

}

void qilin_open()
{
     object room = find_object("/d/city3/shudao8");
     if (! room)
       room = load_object("/d/city3/shudao8");

    room->set("exits/qilinku", QILIN);
    
     message("vision", HIG"【" HIR"江湖傳言" HIG"】" HIW
                "：成都城外洪水退去，麒麟窟重現世間。\n"NOR,users());
      
    remove_call_out("qilin_close");
    call_out("qilin_close", 600, room); //十分種後關閉
}

void qilin_close(object room)
{
     if ( room && room->query("exits/qilinku"));
         room->delete("exits/qilinku");

     message("vision", HIG"【" HIR"江湖傳言" HIG"】" HIW
                "：成都城外洪水洶湧，麒麟窟再次消失在人世間。\n"NOR,users());

    remove_call_out("qilin_open");
  //  call_out("qilin_open", 3600 * 6); //定六小時開一次口
   call_out("qilin_open", 1800); //測試時定半小時開一次口

}



