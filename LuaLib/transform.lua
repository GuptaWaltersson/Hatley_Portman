local transform = {}
transform.__index = transform
local vector = require("vector")

function transform.new(p,r,s)
    assert(p==nil or vector.isvector(p), "transform new- expected args: vector or nil")
    local t = {
        position = p or vector.new(),
        rotation = r or vector.new(),
        scale = s or vector.new()
    }
    setmetatable(t,transform)
    return t
end

function transform.istransform(t)
    return getmetatable(t) == transform
end

function transform.__newindex(t,k,v)
    print("transform - not able to assign new field")
end

function transform.__tostring(t)
    print("Table:")
    print(t.position)
    print(t.rotation)
    print(t.scale)
    return "\n"
end

function transform.__unm(t)
    t.position = vector.__unm(t.position)
    t.rotation =vector.__unm(t.rotation)
    t.scale =vector.__unm(t.scale)
    return t
end

function transform.__add(a,b)
    assert(transform.istransform(a) and transform.istransform(b), "Transform add - Excpected args: transform, transform")
    pos = a.position + b.position
    rot = a.rotation + b.rotation
    sca = a.scale + b.scale
    return transform.new(pos,rot,sca)
end

function transform.__sub(a,b)
    assert(transform.istransform(a) and transform.istransform(b), "Transform sub - Excpected args: transform, transform")
    pos = a.position - b.position
    rot = a.rotation - b.rotation
    sca = a.scale - b.scale
    return transform.new(pos,rot,sca)
end

function transform.__eq(a,b)
    assert (transform.istransform(a) and transform.istransform(b), "Transform eq- Expected args: transform, transform")
    return (a.position == b.position and a.rotation == b.rotation and a.scale == b.scale)
end


return setmetatable (transform, {
    __call = function(_,...)
        return transform.new(...)
    end
})


