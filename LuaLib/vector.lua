local vector = {}
vector.__index = vector
function vector.new(x,y,z) 
    local t = {
        x = x or 0,
        y = y or 0,
        z = z or 0
    }
    setmetatable(t,vector)
    --print(tostring(t))
    return t
end

function vector.isvector(t)
    if getmetatable(t) == vector then
        return true
    else
        return false
    end
end

function vector.__newindex(t,k,v)
    print ("vector - not possible to assign new field")
end

function vector.__tostring(a)
    return ("( "..a.x..", "..a.y..", "..a.z.." )")
end

function vector.__unm(t)
    t.x = -t.x
    t.y = -t.y
    t.z = -t.z

    return t
end

function vector.__add(a,b)
    assert( vector.isvector(a) and vector.isvector(b),"vector sub - excpected args: vector, vector") 
    x = a.x + b.x
    y = a.y + b.y
    z = a.z + b.z

    c = vector.new(x,y,z)
    return c

end


function vector.__sub(a,b)
    assert( vector.isvector(a) and vector.isvector(b),"vector sub - excpected args: vector, vector") 
    x = a.x - b.x
    y = a.y - b.y
    z = a.z - b.z

    return vector.new(x,y,z)

end

function vector.__mul (a,b)
    if (vector.isvector(a) and vector.isvector(b)) then
        return vector.new(a.x*b.x,a.y*b.y,a.z*b.z)
    elseif vector.isvector(a) and type(b) == "number" then
        return vector.new(a.x*b, a.y*b,a.z*b)
    elseif vector.isvector(b) and type(a) == "number" then
        return vector.new(b.x*a,b.y*a,b.z*a)
    elseif type(a) == "number" and type(b) == "number" then
        return a*b
    else
        print("invalid input")
    end
end

function vector.__div(a,b)
    if (vector.isvector(a) and vector.isvector(b)) then
        return vector.new(a.x/b.x,a.y/b.y,a.z/b.z)
    elseif vector.isvector(a) and type(b) == "number" then
        return vector.new(a.x/b, a.y/b,a.z/b)
    elseif vector.isvector(b) and type(a) == "number" then
        return vector.new(b.x/a,b.y/a,b.z/a)
    elseif type(a) == "number" and type(b) == "number" then
        return a/b
    else
        print("invalid input")
    end
end

function vector.__eq(a,b)
    assert( vector.isvector(a) and vector.isvector(b),"vector sub - excpected args: vector, vector") 
    return (a.x == b.x and a.y==b.y and a.z==b.z)
end

function vector:length()
    return math.sqrt(self.x*self.x+ self.y*self.y + self.z*self.z)
end

return setmetatable(vector, {
    __call = function(_,...)
        return vector.new(...)
    end
})


--return vector