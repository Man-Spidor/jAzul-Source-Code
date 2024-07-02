#ifndef IMAGE_H
#define IMAGE_H

class Texture;
struct jAzulRect;

/// @class Image
/// Represents an image with a texture and a rectangular region.
/// 
/// This class provides functionality to manage an image with a texture and a specified rectangular region.
class Image
{
public:
    /// Default constructor.
    Image();

    /// Constructor to initialize the image with a texture and rectangle.
    Image(Texture* pTexture, jAzulRect* pRect);

    /// Copy constructor.
    Image(const Image& other) = default;

    /// Copy assignment operator.
    Image& operator=(const Image& other) = default;

    /// Move constructor.
    Image(Image&& other) = default;

    /// Move assignment operator.
    Image& operator=(Image&& other) = default;

    /// Destructor.
    ~Image();

    /// Set the texture and rectangle for the image.
    /// @param pTexture Pointer to the texture.
    /// @param pRect Pointer to the rectangle.
    void Set(Texture* pTexture, jAzulRect* pRect);

public:
    Texture* pText; ///< Pointer to the texture.
    jAzulRect* pRect; ///< Pointer to the rectangle.
};

#endif // IMAGE_H
