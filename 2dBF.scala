class Filter2D {
    val bits: Int = 61;
    var x: Long;
    var y: Long;
    var arr: Array[Array[Long]];
    def dim(Long p, Long q) = {
        x = p;
        y = q;
    }
    def allocate(): Array[Array[Long]] = {
        arr = Array.ofDim[Long](x, y);
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

class RoBF {
    
}