class Filter2D {
    val bits: Int = 61;
    var x: Long;
    var y: Long;
    var arr: Array[Array[Long]];
    def dim(Long p, Long q) = {
        x = p;
        y = q;
    }
    def allocate {
        this.arr = Array.ofDim[Long](x, y);
        for (i <- 0 until x; j <- 0 until y) {
            arr(i)(j) = 0
        }
        println("\nAllocated and Initilized 2DBF Successfully...\n")
    }
    def __set__(h: Long) = {
        var i: Int = h % x;
        var j: Int = h % y;
        var pos: Int = h % bits;
        arr(i)(j) = arr(i)(j) | (1L << pos);
    }
    def __test__(h: Long) = {
        var i: Int = h % x;
        var j: Int = h % y;
        var pos: Int = h % bits;
        return ((arr(i)(j) & (1L<<pos))>>pos);
    }
    def __del__(h: Long) = {
        var i: Int = h % x;
        var j: Int = h % y;
        var pos: Int = h % bits;
        var p: Long = (1L << pos);
        if (p == arr(i)(j) & (1L<<pos)) {
            a(i)(j) = a(i)(j)^p
        }
    }
    def __free__() = {
        arr = null
        println("\nMemory freed successfully...\n")
    }
}


class RoBF(n: Long, err: Float=0.001f) {
    import scala.math
    import Prime.prime;
    var filter: Filter2D = new Filter2D;
    var size: Long = 0;
    var memory: Long;
    var seed1,seed2,seed3,seed4,seed5: Int;

    def initSeed {
        this.seed1=7689571;
        this.seed2=15485863;
        this.seed3=98899;
        this.seed4=71287;
        this.seed5=101653;
    }

    def this(n: Long, err: Float=0.001f) = {
        println("\nInitializing 2DBF...\n")
        this.memory = -((n * math.log(err)) / math.pow(math.log(2), 2));
        
        val a,b,c,d,f: Int;
        val k: Long = this.memory / (2 * 64);
        f = math.sqrt(k);
        val i: Any = Prime.selectPrime(f);
        a = Prime.prime(ì/2 + 3);
        b = Prime.prime(ì/2 - 3);
        this.filter.dim(a, b);
        println("\n2DBF dimensions: " + a + " x " + b + "\n");
        size += (a*b)*64;
    }
    
    def insert(buff: Char*, i: Int)
    {
        
    }
}