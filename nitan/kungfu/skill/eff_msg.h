// eff_msg.h
/*  在相應的perform里加上：
        #include "/kungfu/skill/eff_msg.h";
        int p;
        p=query("qi", target)*100/query("max_qi", target);
        msg += damage_msg(damage, "瘀傷");
        msg += "( $n"+eff_status_msg(p)+" )\n";  
  或者 msg += "( $n"+status_msg(p)+" )\n";
*/
#include <ansi.h>
string eff_status_msg(int ratio)
{
        if (ratio==100) return HIG"看起來氣血充盈，並沒有受傷。"NOR;
        if (ratio > 95) return HIG"似乎受了點輕傷，不過光從外表看不大出來。"NOR;
        if (ratio > 90) return HIY"看起來可能受了點輕傷。"NOR;
        if (ratio > 80) return HIY"受了幾處傷，不過似乎並不礙事。"NOR;
        if (ratio > 60) return HIY"受傷不輕，看起來狀況並不太好。"NOR;
        if (ratio > 40) return HIR"氣息粗重，動作開始散亂，看來所受的傷着實不輕。" NOR;
        if (ratio > 30) return HIR"已經傷痕累累，正在勉力支撐着不倒下去。"NOR;
        if (ratio > 20) return HIR"受了相當重的傷，只怕會有生命危險。"NOR;
        if (ratio > 10) return RED"傷重之下已經難以支撐，眼看就要倒在地上。"NOR;
        if (ratio > 5 ) return RED "受傷過重，已經奄奄一息，命在旦夕了。"NOR;
        return RED"受傷過重，已經有如風中殘燭，隨時都可能斷氣。"NOR;
}

string status_msg(int ratio)
{
        if( ratio==100 ) return HIG"看起來充滿活力，一點也不累。"NOR;
        if( ratio > 95 ) return HIG"似乎有些疲憊，但是仍然十分有活力。"NOR;
        if( ratio > 90 ) return HIY"看起來可能有些累了。"NOR;
        if( ratio > 80 ) return HIY"動作似乎開始有點不太靈光，但是仍然有條不紊。"NOR;
        if( ratio > 60 ) return HIY"氣喘噓噓，看起來狀況並不太好。"NOR;
        if( ratio > 40 ) return HIR"似乎十分疲憊，看來需要好好休息了。"NOR;
        if( ratio > 30 ) return HIR"已經一副頭重腳輕的模樣，正在勉力支撐着不倒下去。"NOR;
        if( ratio > 20 ) return HIR"看起來已經力不從心了。"NOR;
        if( ratio > 10 ) return RED"搖頭晃腦、歪歪斜斜地站都站不穩，眼看就要倒在地上。"NOR;
        return RED"已經陷入半昏迷狀態，隨時都可能摔倒暈去。"NOR;
}

string damage_msg(int damage, string type)
{
        string str;

        if( damage == 0 ) return "結果沒有造成任何傷害。\n";

        switch( type ) {   
        case "擦傷":
        case "割傷":
                if( damage < 10 ) return "結果只是輕輕地劃破$p的皮肉。\n";
                if( damage < 50 ) return "結果在$p$l劃出一道細長的血痕。\n";
                if( damage < 100 ) return "結果「嗤」地一聲，在$n身上劃出一道傷口！\n";
                if( damage < 170 ) return "結果「嗤」地一聲，在$n身上劃出一道血淋淋的傷口！\n";
                if( damage < 280 ) return "結果「嗤」地一聲，在$n身上劃出一道又長又深的傷口，濺得$N滿臉鮮血！\n";
                return "結果只聽見$n一聲慘嚎，$w已在$p$l劃出一道深及見骨的可怕傷口！！\n";
                break;
        case "刺傷":
                if( damage < 10 ) return "結果只是輕輕地刺破$n的皮肉。\n";
                if( damage < 50 ) return "結果在$n$l刺出一個創口。\n";
                if( damage < 100 ) return "結果「噗」地一聲刺入了$n$l寸許！\n";
                if( damage < 170 ) return "結果「噗」地一聲刺進$n的$l，使$p不由自主地退了幾步！\n";
                if( damage < 280 ) return "結果「噗嗤」地一聲，$w已在$n$l刺出一個血肉模糊的血窟窿！\n";
                return "結果只聽見$n一聲慘嚎，$w已在$p的$l對穿而出，鮮血濺得滿地！！\n";
                break;
        case "砸傷":
                if( damage < 20 ) return "結果只是輕輕地碰撞到了$n一下，沒有造成什麼傷害。\n";
                if( damage < 60 ) return "結果$w只將$n的$l砸出一塊瘀紅。\n";
                if( damage < 120 ) return "結果「啪」地一聲，$w打中$n的$l，登時腫了一塊老高！\n";
                if( damage < 240 ) return "結果$w重重得擊中$n的$l，打得$p倒退數步，「哇」地吐出一大口鮮血！\n";
                if( damage < 380 ) return "結果只聽見「硼」地一聲巨響，$w打在$n身上，將$p像一捆稻草般擊飛出去！\n";
                return "只見$w重重地撞擊在$n的身上，幾聲骨碎聲中，$p象散了架似的癱了下去！！\n";
                break;
        case "瘀傷":
                if( damage < 10 ) return "結果只是輕輕地碰到，比拍蒼蠅稍微重了點。\n";
                if( damage < 20 ) return "結果在$p的$l造成一處瘀青。\n";
                if( damage < 40 ) return "結果一擊命中，$n的$l登時腫了一塊老高！\n";
                if( damage < 80 ) return "結果一擊命中，$n悶哼了一聲顯然吃了不小的虧！\n";
                if( damage < 120 ) return "結果「砰」地一聲，$n退了兩步！\n";
                if( damage < 200 ) return "結果這一下「砰」地一聲打得$n連退了好幾步，差一點摔倒！\n";
                if( damage < 300 ) return "結果重重地擊中，$n「哇」地一聲吐出一口鮮血！\n";
                if( damage < 400 ) return "結果只聽見「砰」地一聲巨響，$n像一捆稻草般飛了出去！！\n";
                return "只聽見$n一聲慘叫，整個身體象斷了線的風箏一樣飛了出去！！\n";
                break;
        case "內傷":
                if( damage < 10 ) return "結果只是把$n打得退了半步，毫髮無損。\n";
                if( damage < 20 ) return "結果$n痛哼一聲，在$p的$l造成一處瘀傷。\n";
                if( damage < 50 ) return "結果一擊命中，把$n打得痛得彎下腰去！\n";
                if( damage < 100 ) return "結果$n悶哼了一聲，臉上一陣青一陣白，顯然受了點內傷！\n";
                if( damage < 200 ) return "結果$n臉色一下變得慘白，昏昏沉沉接連退了好幾步！\n";
                if( damage < 300 ) return "結果重重地擊中，$n「哇」地一聲吐出一口鮮血！\n";
                if( damage < 400 ) return "結果「轟」地一聲，$n全身氣血倒流，口中鮮血狂噴而出！\n";
                return "結果只聽見幾聲喀喀輕響，$n一聲慘叫，像灘軟泥般塌了下去！！\n";
                break;   
        case "震傷":                
                if( damage < 100 ) return "結果$n受到$N的內力反震，悶哼一聲。\n";
                if( damage < 200 ) return "結果$n被$N以內力反震，「嘿」地一聲退了兩步。\n";
                if( damage < 300 ) return "結果$n被$N以內力一震，胸口有如受到一記重錘，連退了五六步！\n";
                return "結果$n被$N的內力一震，眼前一黑，身子向後飛出丈許！！\n";
                break;   
        case "抓傷":     
                if( damage < 10 ) return "結果只是在$n$l處輕輕刮過，沒有什麼傷害。\n";
                if( damage < 25 ) return "結果$n皺了皺眉，$p的$l已經被拉出了一道淺淺的血痕。\n";
                if( damage < 50 ) return "結果拉下來$n$l的一點皮肉，疼得$p「哇哇」怪叫了起來！\n";
                if( damage < 100 ) return "結果「唰」地一聲，$n的$l上頓時被抓出五道血痕，鮮血流了出來！\n";
                if( damage < 200 ) return "結果$n疼得大叫一聲，$p$l上被抓出了幾道深深的血溝，鮮血直流！\n";
                if( damage < 300 ) return "結果只聽見$n一聲慘嚎，$N的手抓已在$p的$l處刺出了五個血肉模糊的窟窿！\n";
                if( damage < 400 ) return "結果「啊」地一聲慘叫，$n身上$p處被$N抓下了一大片皮肉，鮮血橫飛滿地！！\n";
                return "結果伴隨着$n一聲悽慘的嚎叫，直透$p$l處，連皮帶肉扯下一大塊，露出了血淋淋的骨頭！！\n";
                break;       
        default:
                if( !type ) type = "傷害";
                str =  "結果造成非常可怕的嚴重";
                if( damage < 230 ) str = "結果造成極其嚴重的";
                if( damage < 170 ) str = "結果造成十分嚴重的";
                if( damage < 120 ) str = "結果造成相當嚴重的";
                if( damage < 80 ) str = "結果造成頗為嚴重的";
                if( damage < 50 ) str = "結果造成一處嚴重";
                if( damage < 30 ) str = "結果造成一處";
                if( damage < 20 ) str = "結果造成輕微的";
                if( damage < 10 ) str =  "結果只是勉強造成一處輕微";
                return str + type + "！\n";
        }
}