// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping staff_obj = ([
        "/d/xueshan/obj/senggun":18,                  //雪山六個僧兵、葛倫布
        "/d/xueshan/obj/mugun":22,                    //雪山庫房
        "/d/xueshan/obj/fachu":25,                    //雪山祭祀喇嘛（四個）
        "/d/xiangyang/npc/obj/mugun":5,               //襄陽木匠購買
        "/d/village/npc/obj/stick":5,                 //峨嵋小販、少林小販、武功鎮小販
        "/d/tulong/yitian/npc/obj/tiezhang":20,       //杖僧
        "/d/tulong/yitian/npc/obj/spear":10,          //蒙古官兵（二十五個）
        "/d/tulong/tulong/npc/obj/flag":25,           //王盤山島邊四個教眾
        "/d/shaolin/obj/qimeigun":16,                 //澄寂、澄靈、慧潔尊者、慧虛尊者、道塵禪師索要
        "/d/shaolin/obj/chanzhang":12,                //貢唐倉國師、澄滅、澄欲、慧空尊者、慧修尊者、玄難大師、道塵禪師索要
        "/d/quanzhou/npc/obj/huoqiang":35,            //紅毛鬼
        "/d/quanzhen/npc/obj/stick":5,                //全真小販
        "/d/mingjiao/obj/qimeigun":35,                //聞蒼鬆
        "/d/mingjiao/obj/langyabang":30,              //吳勁草、莊錚
        "/d/mingjiao/obj/chanzhang":1,                //暫時無處獲取
        "/d/huanghe/npc/obj/tieqiao":30,              //採石人（兩個）
        "/d/huanghe/npc/obj/fork":35,                 //侯通海
        "/d/heimuya/npc/obj/shutonggun":32,           //張乘風、張乘雲
        "/d/heimuya/npc/obj/leizhendang":35,          //趙鶴
        "/d/heimuya/npc/obj/gangzhang":35,            //上官雲
        "/d/hangzhou/obj/shuzhi":15,                  //杭州山路、蘇州虎丘山、黃河樹林
        "/d/hangzhou/honghua/obj/tiejiang":30,        //蔣四根、沙通天
        "/d/guiyun/npc/obj/gancheng":35,              //全金發
        "/d/guiyun/npc/obj/biandan":8,                //南希仁、買賣提購買
        "/d/foshan/obj/shuzhi":18,                    //佛山林間道
        "/d/city/obj/zhubang":5,                      //揚州林間小屋、蘇州小販購買、俠客島武器庫
        "/d/city/obj/shuzhi":10,                      //好多地方都有
        "/d/city/obj/branch4":16,                     //蛇谷
        "/d/city/obj/branch3":16,                     //蛇谷
        "/d/city/obj/branch2":16,                     //蛇谷
        "/d/city/npc/obj/zhubang":1,                  //暫時無處獲取
        "/d/changan/npc/obj/shawei":22,               //長安衙役（四個）
        "/d/changan/npc/obj/gangzhang":1,             //暫時無處獲取
        "/d/baituo/obj/shezhang":25,                  //白駝武器庫、歐陽峰
        "/d/baituo/obj/lingshezhang":10,              //向歐陽峰要，無限多個
        "/d/baituo/npc/obj/shezhang":1,               //暫時無處獲取
        "/clone/weapon/zhubang":10,                   //燕子塢試劍台、屠龍居
        "/clone/weapon/xiangmo-chu":35,               //達而巴
        "/clone/weapon/tiegun":5,                     //到處都有
        "/clone/weapon/qimeigun":1,                   //暫時無處獲取
        "/clone/weapon/gshezhang":1,                  //暫時無處獲取
        "/clone/weapon/gshezhan":15,                  //向歐陽克要
        "/clone/weapon/gangzhang":15,                 //很多隨機NPC都有
        "/clone/weapon/changqiang":12,                //比較多
        "/clone/misc/bone":5,                         //人骨頭
        "/kungfu/class/gaibang/yuzhu_zhang":35,       //洪七公
        "/kungfu/class/gaibang/obj/yuzhu_zhang":1,    //暫時無處獲取
        "/kungfu/class/dali/obj/diaogan":35,          //褚萬裡
]);

int check_value(string filename)
{
        if (undefinedp(staff_obj[filename])) return 0;
        return staff_obj[filename];
}
