function Image(img)
  return pandoc.RawInline('html',
    '<p align="center"><img src="' ..
    img.src ..
    '" alt="' ..
    (img.caption[1] and img.caption[1].text or '') ..
    '"></p>')
end